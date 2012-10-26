<?php
/**
 * @file
 * Block related hook implementations for the BShare-module.
 */

// ---------------------------------------------------------------------------------

/**
 * Implements hook_block_info().
 */
function bshare_block_info() {
	$blocks['bshare_block'] = array(
		'info' => t('BShare'),
	);

	return $blocks;
}

/**
 * Implements of hook_block_view().
 */
function bshare_block_view($delta='') {
	$block = array();

	if( variable_get('bshare_location', 'content') != 'block' )  return;

	switch ($delta) {
		case 'bshare_block':

			foreach( array('BShare', 'main') as $k => $name ) {

				drupal_add_js(
					drupal_get_path('module', 'bshare') . "/{$name}.js",
					array(
						'group' => 'bshare',
						'weight' => $k + 10,
					)
				);
			}

			$block['content'] = bshare_get_HTML();
		break;
	}

	return $block;
}