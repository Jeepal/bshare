<?php
/**
 * @file
 * Administrative page callbacks for the BShare-module.
 */

// ---------------------------------------------------------------------------------

/**
 * This is the main configuration form for the admin page.
 */
function bshare_configuration_form($form, &$form_state)
{
	global $base_url;

	$form['button'] = array(
		'#type'		=> 'fieldset',
		'#title'	=> t('BShare Settings')
	);

	$form['button']['setting1'] = array(
		'#type'		=> 'fieldset',
		'#title'	=> t("Display Style:")
	);

	// Display Style
	$form['button']['setting1']['display_style'] = array(
		
		'#options' => array(
			'BAR'		 => t('Bar'),
			'BUTTON'	 => t('Button'),
			'SUSPENSION' => t('Suspension')
		),

		'#default_value'	=> variable_get('display_style', 'BAR'),
		'#type'				=> 'radios',
		'#required'			=> TRUE,
	);

	$form['button']['setting2'] = array(
		'#type'		=> 'fieldset',
		'#title'			=> t("Button Style:")
	);

	// Button Style
	$form['button']['setting2']['button_style'] = array(

		'#options' => array(
			BSHARE_BUTTON_STYLE_MINI		=> t('Mini'),
			BSHARE_BUTTON_STYLE_STANDARD	=> t('Standard'),
			BSHARE_BUTTON_STYLE_BIG			=> t('Big')
		),

		'#default_value'	=> variable_get('button_style', BSHARE_BUTTON_STYLE_STANDARD),
		'#type'				=> 'radios',
		'#required'			=> TRUE
	);

	$form['button']['setting3'] = array(
		'#type'		=> 'fieldset',
		'#title'			=> t("Share Views:")
	);

	// Share Views
	$form['button']['setting3']['share_views'] = array(

		'#options' => array(
			'true'	=> t('YES'),
			'false'	=> t('NO'),
		),

		'#default_value'	=> variable_get('share_views', 'true'),
		'#type'				=> 'radios',
		'#required'			=> TRUE
	);

	$form['button']['setting4'] = array(
		'#type'		=> 'fieldset',
		'#title'	=> t('Location')
	);

	$form['button']['setting4']['bshare_location'] = array(
		'#type' => 'radios',
		'#options' => array(
			'content' => t('Node content'),
			'block' => t('Block'),
			'links' => t('Links area'),
			'custom' => t('Custom'),
		),

		'#default_value' => variable_get('bshare_location', 'content'),
		'#description' => t('Select where the ShareThis widget should appear. When selected to display as a block, you must choose which region to display the <em>ShareThis block</em> in from the <a href="@blocksadmin">Blocks administration</a>.', array('@blocksadmin' => url('admin/structure/block')))
  );

	return system_settings_form($form);
}