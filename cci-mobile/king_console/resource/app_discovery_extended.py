# kv resources
const_app_discovery_ids = {
					   'app_discovery_extended_screen' :
"""
AppDiscoveryScreen:
	GridLayout
		orientation: 'horizontal'
		cols: 1
		Accordion:
			id: appdiscovery_accordion
			orientation: 'vertical'
			AccordionItem:
				title: 'baby snmp'
			AccordionItem:
				title: 'upnp'
			AccordionItem:
				title: 'ip geography'
				id: view_ip_geo
			AccordionItem:
				title: 'cci-maelstrom'
				GridLayout
					orientation: 'horizontal'
					cols: 1
					ActionBar:
						pos_hint: {'top':1}
						ActionView:
							use_separator: True
							ActionPrevious:
								title: 'king console'
								with_previous: False
								on_press: root._on_full_screen()
								app_icon: 'king-console32.png'
							ActionButton:
								text: 'back'
								on_press: app._manip_extended_window()
							ActionButton:
								text: 'notes'
								id: appdiscovery_note_btn
								#on_press: root._on_arp_monitor_start()
					Carousel:
						id: appdiscovery_carousel_id
						direction: 'right'
						GridLayout:
							orientation: 'horizontal'
							id: console_grid
							cols: 1
							Label:
								text: 'mene mene tekel upharsin'
								color: [ 1, 0 , 0 , 1]
								font_size: 16

"""
,
					 'ip_geography_view' :
"""
BoxLayout:
	orientation: 'vertical'
	id: geography_ip
	GridLayout:
		id: main_grid
		cols: 1
		orientation: 'horizontal'
		#size_hint_y: None
		#size: ( 480 ,600 )
		GridLayout:
			id: geography_grid
			orientation: 'horizontal'
			cols: 1
			GridLayout
				orientation: 'horizontal'
				cols: 2
				size_hint_y: 0.20
				Button:
					id: more_app_btn
					text: '...'
					color: [224 / 255.0 , 224 / 255.0 , 224 / 255.0 ,224 / 255.0]
				Button:
					id: do_geo_btn
					text: 'execute ip geo'
					color: [224 / 255.0 , 224 / 255.0 , 224 / 255.0 ,224 / 255.0]
			Label:
				text: 'geo resource ip:'
				size_hint_y: 0.15
			TextInput:
				text: '173.167.195.34'
				id: ip_geo_metric
				size_hint_y: 0.25
				cursor_blink: True
				readonly: False
				multiline: True
			Label:
				text: 'geo authorization file:'
				size_hint_y: 0.15
			TextInput:
				text: 'ip_geo_key'
				size_hint_y: 0.25
				id: ip_geo_key
				cursor_blink: True
				readonly: False
				multiline: True

"""
,
	'text_scroller' :
"""
ScrollView:
	id: scrlv
	TextInput:
		text: 'foo'
		size_hint: 1, None
		cursor_blink: True
		background_color: [1,0,0,0]
		foreground_color: [1,1,1,1]
		multiline: True
		id: tx_in
		font_size: 16
		readonly: True
		height: max( (len(self._lines)+1) * self.line_height, scrlv.height)
"""
,
}
