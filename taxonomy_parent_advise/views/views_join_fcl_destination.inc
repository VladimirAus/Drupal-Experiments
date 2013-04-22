<?php

class views_join_fcl_destination extends views_join {

  function construct($table = NULL, $left_table = NULL, $left_field = NULL, $field = NULL, $extra = array(), $type = 'LEFT') {
    //parent::construct($table, $left_table, $left_field, $field, $extra, $type);

    $this->extra_type = 'OR';
    // if (!empty($this->definition['extra type'])) {
    //   $this->extra_type = strtoupper($this->definition['extra type']);
    // }
    // $this->type = !empty($this->definition['type']) ? strtoupper($this->definition['type']) : 'LEFT';
    // $this->table = ;
    // $this->field = ($table['alias']).".index_trail LIKE CONCAT(".($table['alias']).".index_trail, '%')";

    if (!empty($table)) {
      $this->table = $table;
      $this->left_table = $left_table;
      $this->left_field = $left_field;
      $this->field = $field;
      $this->extra = $extra;
      $this->type = strtoupper($type);
    }
    elseif (!empty($this->definition)) {
      // if no arguments, construct from definition.
      // These four must exist or it will throw notices.
      $this->table = $this->definition['table'];
      $this->left_table = $this->definition['left_table'];
      $this->left_field = $this->definition['left_field'];
      $this->field = $this->definition['field'];
      if (!empty($this->definition['extra'])) {
        $this->extra = $this->definition['extra'];
      }
      if (!empty($this->definition['extra type'])) {
        $this->extra_type = strtoupper($this->definition['extra type']);
      }

      $this->type = !empty($this->definition['type']) ? strtoupper($this->definition['type']) : 'LEFT';
    }
  }

  function build_join($select_query, $table, $view_query) {
    dpm($table);
    $this->extra = 
      "taxonomy_term_data_field_data_field_filter_destination.tid = taxonomy_term_data_children.tid OR " . 
      ($table['alias']).".index_trail LIKE CONCAT(".($table['alias']).".index_trail, '%')";
    // $this->extra_type = "OR";
    dpm($this);
    parent::build_join($select_query, $table, $view_query);
  }
}
 