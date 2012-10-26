/*
 * Drupal BShare Module BShare jQuery plugin v0.1
 *
 * Copyright 2012-2013, Zhang Zhao, netwolf103@gmail.com
 */

(function($){

// Constructor function
$.BShare = function( elem, options ) {
	this.$elem = $(elem);
	this.opts = $.extend( {}, $.fn.BShare.defaults, options );

	this.init();
};

// Parent class
$.BShare.prototype = {

	 // DOM Initialization
	 init: function(){
		var _this = this;

		_this.$elem.each(function(){
			bShare.addEntry({
				title:		$(this).find( _this.opts.titleDOM ).text(),
				url:		_this.opts.siteURL + $(this).find( _this.opts.titleDOM ).attr('href'),
				summary:	$(this).find( _this.opts.contentDOM ).text(),
			});
		});
	 },
};

// Plug the main entrance. 
$.fn.BShare = function( options ){
	return new $.BShare( this, options );
}

// Default configure
$.fn.BShare.defaults = {
	siteURL:	'',
	titleDOM:	'h2 > a',
	contentDOM: '.content'
};

})(jQuery);