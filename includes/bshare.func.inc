<?php
/**
 * @file
 * Functions for the BShare-module.
 *
 * bshare参数说明：
 *	uuid	站长的UUID（Publisher UUID）。如果要追踪分享数据则必须提供此选项，在bShare后台添加网站即可得到UUID。
 *	lang	语言，可以是简体中文 (zh), 英文 (en), 或繁體中文 (zh_TW)
 *	pop		定义分享小窗口的弹出方式。可以是：
		-1: 不弹出小窗口
		0: 自动选择向上或者向下弹出小窗口
		1: 总是向下弹出小窗口
		2: 总是向上弹出小窗口
 *	popbgc	弹出小窗口的顶部和底部的背景颜色，可以是CSS中color属性支持的任意值。
 *	poptxtc	弹出小窗口的顶部和底部的文字颜色，可以是CSS中color属性支持的任意值。
 *	mdiv	定义大分享窗口（即点更多后出现的弹窗）的显示方式。可以是：
		-1: 不弹出大分享窗口
		 0: 自动弹出分享窗口
 *	style	按钮式样，有以下几种情况：
		bShare预定义的式样，包括以下几种：0 (文字), 1 (默认), 2 (列式), 3 (浮动), 4 (浮动图片), 5 (三角),
    10 (苗条型), 11 (胖犁型).
		不加载分享按钮。如果按钮是通过bShare客户端API自定义的，则可以将style设置为-1。
		自定义图片。如果想要使用自定义的图片作为按钮，则可以讲style设置为999.
 *
 * 注意：以下参数只对某些预定义式样有效
 *	fs			浮动式样，可以为0 (不浮动), 1 (页面顶部浮动), 2 (页面底部浮动), 3 (页面左侧浮动), 4 (页面右侧浮动). 式样2 (列表式) 支持静态及上下浮动，式样3 (浮动), 4 (浮动图片) 支持左右浮动，式样5 (三角) 上下左右都可以，其他式样的按钮都不能浮动。
 *	bgcolor		背景颜色，可以是CSS中color属性支持的任意值，也可以设置为none，则按钮为透明且没有边框。
 *	textcolor	文字颜色，可以是CSS中color属性支持的任意值。
 *	bp			按钮上直接显示的平台，以英文逗号分隔的平台代码。对于普通按钮和浮动按钮，这些平台显示在鼠标移过时弹出的小窗口中；对于列表式，则直接显示在列表中。
 *	ssc			是否显示分享计数，true或者false。
 *	sn			是否显示分享平台名称，true或者false。只对式样2（列表式）起作用，默认是false。
 *	text		显示的文字内容，默认是"分享"或者"分享到"，用于文本按钮、列式按钮等式样中。
注：由于Safari浏览器的编码机制，当为非utf-8页面安装按钮并需要设置text的值为中文时，请将中文进行utf-8编码后再对text赋值，如用 text=%E5%88%86%E4%BA%AB%E5%88%B0 代替 text=分享到。
 *	img			用于自定义按钮图片，参数为图片的URL（已编码）。使用时必须将style设置为4（浮动式）或者999（按钮式），并同时指定h和w参数，分别为按钮图片的高度和宽度，以px（像素）为单位。
 */

// ---------------------------------------------------------------------------------

if( !defined('BSHARE_SCRIPT_LABEL') )
	define('BSHARE_SCRIPT_LABEL', '<script type="text/javascript" charset="utf-8" src="http://static.bshare.cn/b/%s"></script>');

/**
 * bshare_get_button_HTML is the function that creates the BShare code
 *
 * @parsm string
 *		$langcode
 * @return string
 */
function bshare_get_HTML( $lang = 'en' ) 
{
	$jsParameter = array(
		'uuid'		=> '',
		'lang'		=> $lang,
		'pop'		=> 0,
		'popbgc'	=> '#f2f2f2',
		'poptxtc'	=> '#333333',
		'mdiv'		=> 0,
		'style'		=> 1,
		'fs'		=> 0,
		'bgcolor'	=> '#f90',
		'textcolor' => '#fff',
		'bp'		=> '',
		'ssc'		=> variable_get('share_views', 'true'),
		'sn'		=> 'false',
		'text'		=> t('Share to'),
		'img'		=> '',
		'btnsize'	=> variable_get('button_style', BSHARE_BUTTON_STYLE_STANDARD)
	);

	$function = sprintf( 'bshare_get_%s_HTML', strtolower( variable_get('display_style', 'BAR') ));

	if( !function_exists($function) ) {
		$function = 'bshare_get_button_HTML';
	}

	return $function( $jsParameter );
}

 /**
 * Create bshare button style code.
 *
 * @param array
 *		$QUERY bshare api param
 * @return string
 */
function bshare_get_button_HTML( $QUERY ) 
{
	$shareList = '';
	foreach( 
		array(
			'qzone'			=> t('Share to QZone'),
			'sinaminiblog'	=> t('Share to Sina MiniBlog'),
			'renren'		=> t('Share to RenRen'),
			'qqmb'			=> t('Share to Tencent'),
			'douban'		=> t('Share to Douban'),
			'more bshare-more-icon' => t('Share to Others'),

		) as $name => $label ) {
			$shareList .= sprintf('<a title="%s" class="bshare-%s"></a>', $label, $name);
	}

	$ssc = ($QUERY['ssc'] == 'true') ? '<span class="BSHARE_COUNT bshare-share-count" style="color:#333;">0</span>' : '';

	$html = sprintf( '<div class="%s">%s%s</div>', bshare_get_button_CLASS(), $shareList, $ssc );
	
	$javascript = sprintf( BSHARE_SCRIPT_LABEL, sprintf('buttonLite.js#%s', drupal_http_build_query($QUERY)) );
	$javascript .= sprintf( BSHARE_SCRIPT_LABEL, sprintf('bshareC%s.js', $QUERY['btnsize']) );

	return $html . $javascript;
}

/**
 * Create bshare bar style code.
 *
 * @return string
 */
function bshare_get_bar_HTML( $QUERY ) 
{
	global $base_url;

	$html = sprintf( '<a class="bshareDiv" href="http://www.bshare.cn/share"></a>', $QUERY['text'] );

	$QUERY['style'] = '999';
	$QUERY['w'] = '147';
	$QUERY['h'] = '21';
	$QUERY['img'] = $base_url .'/'. drupal_get_path('module', 'bshare') . '/images/box-shareTo-' . $QUERY['lang'] . '.gif';

	$javascript = sprintf( BSHARE_SCRIPT_LABEL, sprintf('buttonLite.js#%s', drupal_http_build_query($QUERY)) );

	return $html . $javascript;
}

/**
 * Create bshare suspension style code.
 *
 * @return string
 */
function bshare_get_suspension_HTML( $QUERY ) 
{
	$QUERY['style'] = $QUERY['btnsize'] + 2;
	$QUERY['fs'] = 4;

	$javascript = sprintf( BSHARE_SCRIPT_LABEL, sprintf('buttonLite.js#%s', drupal_http_build_query($QUERY)) );

	return $javascript;
}

/**
 * Return BShare style class name.
 *
 * @return string
 */
function bshare_get_button_CLASS() 
{
	$return = 'bshare-custom';

	$classes = array(
		BSHARE_BUTTON_STYLE_MINI	 => '',
		BSHARE_BUTTON_STYLE_STANDARD => 'icon-medium',
		BSHARE_BUTTON_STYLE_BIG		 => 'icon-medium-plus'
	);

	$return .= ' ' . $classes[variable_get('button_style', BSHARE_BUTTON_STYLE_STANDARD)];

	return $return;
}