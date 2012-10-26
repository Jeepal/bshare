<?php
/**
 * @file
 * Note related hook implementations for the BShare-module.
 */

// ---------------------------------------------------------------------------------

if( !defined('BSHARE_SCRIPT_LABEL') )
	define('BSHARE_SCRIPT_LABEL', '<script type="text/javascript" charset="utf-8" src="http://static.bshare.cn/b/%s"></script>');

 /**
 * Implements hook_node_view.
 *
 */
function bshare_node_view( $node, $view_mode, $langcode ) {

	$node->content['bshare'] = array(
		'#tag'	=> 'div',
		'#type'	=> 'html_tag',
		'#value'=> bshare_get_HTML( $langcode ),
	);

	switch( variable_get('bshare_location', 'content') ) {

		
		case 'content':
		case 'links':

			foreach( array('BShare', 'main') as $k => $name ) {

				drupal_add_js(
					drupal_get_path('module', 'bshare') . "/{$name}.js",
					array(
						'group' => 'bshare',
						'weight' => $k + 10,
					)
				);
			}

		break;

		case 'custom':
			$node->content['bshare'] = array();
			drupal_add_js( 'http://static.bshare.cn/b/buttonLite.js', array('type' => 'external') );

			module_invoke_all( 'bshare_custom', $node, $view_mode, $langcode );

		break;

		default:
			$node->content['bshare'] = array();
		break;
	}
}