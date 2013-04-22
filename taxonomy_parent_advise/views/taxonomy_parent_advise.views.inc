<?php

/**
 * @file
 * Provide views data and handlers for taxonomy.module.
 */

/**
 * Implements hook_views_data_alter().
 */
function taxonomy_parent_advise_views_data_alter(&$data) {

  $data['taxonomy_term_data']['index_trail'] = array(
    'title' => t('Taxonomy term children index trail'),
    'help' => t('Relate term to children terms using index trail technique.'),
    'relationship' => array(
      // 'handler' => 'views_handler_relationship',
      'handler' => 'views_handler_relationship_term_index_trail',
      'table alias' => 'ttdchildren',
      'label' => t('term index trail'),
      'group' => t('Taxonomy Term'),
      // 'extra type' => 'OR',
      'base' => 'taxonomy_term_data',
      // 'base field' => 'tid OR {taxonomy_term_data} LIKE CONCAT({taxonomy_term_data}.index_trail, \'%\')',
      'relationship field' => 'tid',
      // 'skip base' => array('taxonomy_term_data', 'taxonomy_term_data'),
      // 'value' => 'CONCAT(taxonomy_term_data.index_trail, "%")',
      // 'extra type' => 'OR',
      // 'label' => t('term index trail'),
      // 'group' => t('Taxonomy Term'),
      // 'base' => 'taxonomy_term_data',
      // 'base field' => 'index_trial',
      // 'numeric' => true,
      // 'extra type' => 'OR',
      // 'extra' => array(
      //   'field' => 'index_trail',
      //   'value' => "CONCAT(taxonomy_term_data.index_trail, '%')",
      //   'numeric' => TRUE,
      //   'operator' => 'LIKE',
      // ),
    ),
    'field' => array(
      'title' => t('Taxonomy term children index trail'),
      'help' => t('Display all taxonomy term parent index trial.'),
      'handler' => 'views_handler_field',
      'no group by' => TRUE,
    ),
  );
}