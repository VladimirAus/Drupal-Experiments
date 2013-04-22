<?php

/**
 * @file
 * Definition of views_handler_relationship_node_term_data.
 */

/**
 * Relationship handler to return the taxonomy terms of nodes.
 *
 * @ingroup views_relationship_handlers
 */
class views_handler_relationship_term_index_trail extends views_handler_relationship  {
  function init(&$view, &$options) {
    parent::init($view, $options);

    // Convert legacy vids option to machine name vocabularies.
    if (!empty($this->options['vids'])) {
      $vocabularies = taxonomy_get_vocabularies();
      foreach ($this->options['vids'] as $vid) {
        if (isset($vocabularies[$vid], $vocabularies[$vid]->machine_name)) {
          $this->options['vocabularies'][$vocabularies[$vid]->machine_name] = $vocabularies[$vid]->machine_name;
        }
      }
    }
  }

  /*
  function option_definition() {
    $options = parent::option_definition();
    $options['vocabularies'] = array('default' => array());
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $vocabularies = taxonomy_get_vocabularies();
    $options = array();
    foreach ($vocabularies as $voc) {
      $options[$voc->machine_name] = check_plain($voc->name);
    }

    $form['vocabularies'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Vocabularies'),
      '#options' => $options,
      '#default_value' => $this->options['vocabularies'],
      '#description' => t('Choose which vocabularies you wish to relate. Remember that every term found will create a new record, so this relationship is best used on just one vocabulary that has only one term per node.'),
    );
    parent::options_form($form, $form_state);
  }
  */

  /**
   * Called to implement a relationship in a query.
   */

  function query() {
    $this->ensure_my_table();

    $def['type'] = empty($this->options['required']) ? 'LEFT' : 'INNER';
    // $this->query->addJoin($def['type'], 'taxonomy_term_data', 'taxonomy_term_data_children', 'taxonomy_term_data_node.index_trail LIKE CONCAT(taxonomy_term_data_node.index_trail, "%")');
    $join = new views_join();
    // $join = new views_join_fcl_destination();
    $join->definition = $this->definition;
    // dpm($this->definition);

    // $def['extra'] = array(
    //   array(
    //     // The table and the IN operator are implicit.
    //     // 'field' => 'index_trail',
    //     // 'value' => "CONCAT(".$this->table_alias.".index_trail, '%')",
    //     // 'operator' => 'LIKE',
    //     // 'numeric' => true,
    //     // 'extra type' => 'OR',
    //     'taxonomy_term_data_node.index_trail LIKE CONCAT(taxonomy_term_data_node.index_trail, "%")'
    //   ),
    // );

    $def['extra'] = null;
    $alias = "taxonomy_term_data_children";
        // "taxonomy_term_data_field_data_field_filter_destination.tid = taxonomy_term_data_children.tid OR " . 
        // ($this->table_alias).".index_trail LIKE CONCAT(".($this->table_alias).".index_trail, '%')";
    $extra = " OR " . $alias.".index_trail LIKE CONCAT(".($this->table_alias).".index_trail, '%')";

    // Construct help
    // http://api.drupal.org/api/views/includes!handlers.inc/function/views_join%3A%3Aconstruct/7
    
    $join->construct('taxonomy_term_data', $this->table_alias, 'tid', 'tid' . $extra, $def['extra'], $def['type']);
    $join->adjusted = FALSE;
    // $this->query->ensure_table('taxonomy_term_data', $this->relationship, $join);

    // dpm($join);
    // $join->extra_type = "OR";
    // $join->operator = "LIKE";

    
    $this->alias = $this->query->add_relationship($alias, $join, 'taxonomy_term_data', $this->relationship);
    
    // $join = new views_join_fcl_destination();
    // $join->definition = $this->definition;
    // $join->construct('taxonomy_term_data');
    // $join->adjusted = FALSE;
    // $this->alias = $this->query->add_relationship($alias, $join, 'taxonomy_term_data', $this->relationship);
    // $this->query->ensure_table('taxonomy_term_data', $this->relationship, $join);

    // dpm($this->query);
    //$this->add_additional_fields();

    // Join to the node table to retrieve the node UID.
    // $join = new views_join();
    // $join->construct('node', $this->table_alias, 'nid', 'nid');
    // $this->query->ensure_table('node', $this->relationship, $join);

    // $this->add_additional_fields();

    // //////////////////////////////////

    // $def = $this->definition;
    // $def['table'] = 'taxonomy_term_data';

    // //$taxonomy_index = $this->query->add_table('taxonomy_index', $this->relationship);
    // $def['left_table'] = $taxonomy_index;
    // $def['left_field'] = 'tid';
    // $def['field'] = 'tid';
    // $def['type'] = empty($this->options['required']) ? 'LEFT' : 'INNER';
    // $query = db_select('taxonomy_term_data', 'td');
    // $query->addJoin($def['type'], 'taxonomy_term_data', 'taxonomy_term_data_children', 'taxonomy_term_data_node.index_trail LIKE CONCAT(taxonomy_term_data_node.index_trail, "%")');
    // $def['table formula'] = $query;


    // if (!array_filter($this->options['vocabularies'])) {
    //   $taxonomy_index = $this->query->add_table('taxonomy_index', $this->relationship);
    //   $def['left_table'] = $taxonomy_index;
    //   $def['left_field'] = 'tid';
    //   $def['field'] = 'tid';
    //   $def['type'] = empty($this->options['required']) ? 'LEFT' : 'INNER';
    // }
    // else {
    //   // If vocabularies are supplied join a subselect instead
    //   $def['left_table'] = $this->table_alias;
    //   $def['left_field'] = 'nid';
    //   $def['field'] = 'nid';
    //   $def['type'] = empty($this->options['required']) ? 'LEFT' : 'INNER';

    //   $query = db_select('taxonomy_term_data', 'td');
    //   $query->addJoin($def['type'], 'taxonomy_vocabulary', 'tv', 'td.vid = tv.vid');
    //   $query->addJoin($def['type'], 'taxonomy_index', 'tn', 'tn.tid = td.tid');
    //   $query->condition('tv.machine_name', array_filter($this->options['vocabularies']));
    //   $query->addTag('term_access');
    //   $query->fields('td');
    //   $query->fields('tn', array('nid'));
    //   $def['table formula'] = $query;
    // }


    // $join = new views_join();

    // $join->definition = $def;
    // $join->construct();
    // $join->adjusted = TRUE;

    // // use a short alias for this:
    // $alias = $def['table'] . '_' . $this->table;

    // $this->alias = $this->query-> ($alias, $join, 'taxonomy_term_data', $this->relationship);
  }
}
