<?php 

/**
 * @file
 * FCL import commands for Drush
 */

/**t
 * Implementation of hook_drush_command().
 */
function fcl_procat_product_import_drush_command() {
  $items = array();
 
  $items['fcl-procat-product-import'] = array(
    'callback' => 'drush_fcl_procat_product_importer',
    'description' => 'Import FCL Procat products.',
    'arguments'   => array(
      'consumer'   => dt('An optional consumer argument. all by default. Examples: all, place1'),
      'url_pattern'   => dt('An optional url alias argument. all by default. Examples: all, place1'),
      'num_products'   => dt('An optional number of products to import argument. all by default. Examples: all, place1'),
      'num_in_batch'   => dt('An optional number of products per batch argument. all by default. Examples: all, place1'),
    ),
  
  );
  $items['fcl-procat-list-import'] = array(
    'callback' => 'drush_fcl_procat_list_import',
    'description' => 'Import lists for FCL products. Examples: all, place2 ',
    'arguments'   => array(
      'arg1'   => dt('An optional list argument. all by default. Examples: all, place1'),
    ),
    //describe options
    'options' => array(
      'arg1' => array(
        'description' => dt('An optional list argument. all by default.'),
        'example_value' => 'all',
        'value' => 'optional',
      ),
    ),
    'examples' => array(
      'drush fcl-procat-list-import' => 'Import lists: all by default (excludes place1 and palce2).',
      'drush fcl-pli all' => 'Import all lists (excludes place1 and palce2).',
      'drush fcl-pli place2' => 'Import place2 list.',
     ),
    'aliases' => array('fcl-pli'),
  );
  $items['fcl-procat-product-delete'] = array(
    'callback' => 'drush_fcl_procat_product_delete_products',
    'description' => 'Delete all FCL Procat products.',
    'arguments'   => array(),
    //describe options
    'options' => array(),
    'examples' => array(
      'drush fcl-procat-product-delete' => 'Delete all existing products entities.',
      'drush fcl-ppd' => 'Delete all existing products entities.',
     ),
    'aliases' => array('fcl-ppd'),
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 */
function fcl_procat_product_import_drush_help($section) {
  switch ($section) {
    case 'drush:fcl-procat-product-import':
      return t("Import procat products. Opional parameter: consumer, URL path alias for products, number of products to import, number of products per batch.");
    case 'drush:fcl-procat-list-import':
      return t("Import procat lists. All lists are imported by default. Opional parameter: list name e.g. place1 or all");
    case 'drush:fcl-procat-list-delete':
      return t("Clear particular or all vocabularies.");
    case 'drush:fcl-procat-product-delete':
      return t("Delete all FCL Procat products.");
  }
}

/**
 * Drush callback to delete content
 *
 *  @param $consumer
 *     String - consumer unique identificator e.g. EscapeTravel
 *  @param $url_pattern
 *     String - URL path alias for products
 *  @param $num_products
 *     Integer - number of products to import
 *  @param $num_in_batch
 *     Integer - number of products per batch
 */
function drush_fcl_procat_product_importer($consumer = null, $url_pattern = null, $num_products = null, $num_in_batch = null) {
  

  // Assign new defaults
  if (isset($consumer)) { // @todo: check if consumer is in the list
    variable_set('fcl_procat_product_import_products_consumer', $consumer);
  }
  if (isset($url_pattern)) { // @todo: check if consumer is in the list
    variable_set('fcl_procat_product_import_product_url_alias', $url_pattern);
  }
  if (isset($num_products) && is_integer((int)$num_products) && ((int)$num_products > 0)) {
    variable_set('fcl_procat_product_import_products_max_number', ((string)$num_products));
  }
  if (isset($num_in_batch) && is_integer((int)$num_in_batch) && ((int)$num_in_batch > 0)) {
    variable_set('fcl_procat_product_import_products_no_per_batch', ((string)$num_in_batch));
  }

  // Display data and run import
  $method = variable_get('fcl_procat_product_import_product_option', 'query');
  $noProducts = variable_get('fcl_procat_product_import_products_max_number', '500'); 
  $noInBatch = variable_get('fcl_procat_product_import_products_no_per_batch', '20'); 
  $consumer = variable_get('fcl_procat_product_import_products_consumer', 'CorporateTravellerAUAllProd');
  $urlAliasPattern = variable_get('fcl_procat_product_import_product_url_alias', 'product/[sku]');
  
  $poduct_desc = $method=="query" ? "Importing ".$noProducts." products" : "All products";

  drush_log($poduct_desc . " in batches of ".$noInBatch." for ".$consumer." consumer.", 'ok');
  // drush_log("Product URL alias pattern: " . $urlAliasPattern, 'ok');
  fcl_procat_product_import_import_products(true);

}

/**
 * Drush callback to delete content
 *
 *  @param $arg1
 *     String - name of the list e.g. all or place2
 */
function drush_fcl_procat_list_import($arg1 = null) {
  //$arg1 = drush_get_option('arg1'); // if you using 
 
  //check if the argument was passed in and just print it out
  $list = "all";
  if (isset($arg1)) {
    if (in_array($arg1, array_keys(fcl_procat_product_import_get_vocabularies()))) {
      drush_log(($arg1 == "all")?"Downloading all lists":("Downloading " . $arg1 . " list"), 'ok');
      $list = $arg1;
    }
    else {
      drush_log("List provided is unkown. Downloading all.", 'warning');
    }
  }
  else {
    drush_log("No list was provided. Downloading all.", 'ok');
  }

  //drush_log('Running my-command', 'ok');
  fcl_procat_product_import_batch_lists($list, true);
}

/**
 * Drush callback to delete product entites
 */
function drush_fcl_procat_product_delete_products() {

  //drush_log('Running my-command', 'ok');
  fcl_procat_product_import_delete_entities('fcl_procat_product', 'fcl_procat_product', true);
}

/**
 * Drush callback to delete taxonomy entites
 */
function drush_fcl_procat_product_delete_list_items($vocabulary) {

  $vKeys = array_keys(fcl_procat_product_import_get_vocabularies());
    if (($vocabulary == "all") || 
      (in_array($vocabulary, array_keys(fcl_procat_product_import_get_vocabularies())))) {
      fcl_procat_product_import_delete_entities('taxonomy_term', $vocab, true);
    }
    else {
      drush_log("Unknown vocabulary.", 'error');
    }
}