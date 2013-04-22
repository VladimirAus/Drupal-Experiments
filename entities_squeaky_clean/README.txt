Clear entities content using drush, admin interface, or address bar.
Supports nodes, taxonomies and custom entities.

=================================
ADMIN INTERFACE:
=================================
Head to admin/config/development/esc to use the interface to clean particular entity.

=================================
ADDRESS BAR EXAMPLES:
=================================
http://yoursite.com/admin/esc/taxonomy_term/holiday_category
- Empty holiday_category dictionary
http://yoursite.com/admin/esc/node/page
- Delete all pages
http://yoursite.com/admin/esc/product/product_postcards
- Delete all product entities from product_postcards bundle

=================================
DRUSH EXAMPLES:
=================================
drush esc taxonomy_term holiday_category
- Empty holiday_category dictionary
drush esc node page
- Delete all pages
drush esc product product_postcards
- Delete all product entities from product_postcards bundle


=================================
CHANGE LOG:
=================================

1.0-alpha1
2013-Mar-27
- Drush script for legacy product removal (VladimirAus)