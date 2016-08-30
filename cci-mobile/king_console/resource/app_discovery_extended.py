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
								app_icon: 'king-console32.png'
							ActionButton:
								text: 'back'
								on_press: app._manip_extended_window()
							ActionButton:
								text: 'notes'
								id: appdiscovery_note_btn
								color: [0,1,0.1]
								#on_press: root._on_arp_monitor_start()
					Carousel:
						id: carousel_id
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
	ScrollView:
		GridLayout:
		    id: main_grid
			cols: 1
			orientation: 'horizontal'
			size_hint_y: None
			size: ( 480 ,400 )
			GridLayout:
				id: geography_grid
				orientation: 'horizontal'
				cols: 1
				Label:
					text: 'geo resource ip:'
				TextInput:
					text: '173.167.195.34'
					id: ip_geo_metric
					cursor_blink: True
					readonly: False
					multiline: True
				Label:
					text: 'geo authorization file:'
				TextInput:
					text: 'ip_geo_key'
					id: ip_geo_key
					cursor_blink: True
					readonly: False
					multiline: True
				Button:
					id: do_geo_btn
					text: 'execute ip geo'
					background_color: [0,0,0,0]
					color: [1,0,0,1]
"""
,
}
