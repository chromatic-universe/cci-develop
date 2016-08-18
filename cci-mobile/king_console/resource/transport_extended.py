

# kv resources
const_transport_resource_ids = {
					   'transport_extended_screen' :
"""
TransportScreen:
	id: transport_screen
    name: 'screen_transport'
	GridLayout
		orientation: 'horizontal'
		cols: 1
		Accordion:
			id: tcp_accordion
			orientation: 'vertical'
			AccordionItem:
				title: 'discovery and port manip'
				Accordion:
					orientation: 'horizontal'
					AccordionItem:
						title: 'classics'
						orientation: 'vertical'
						GridLayout:
							orientation: 'horizontal'
							cols: 1
							ScrollView:
								ListView:
									id: list_view_id
									size_hint_y: .75
									adapter:
										la.ListAdapter(
										data=["firewalk(internal)" , "firewalk(external)"],
										selection_mode='single',
										allow_empty_selection=False,
										cls=lv.ListItemButton)
							TextInput:
								text: 'firewalk scan....'
								id: classics_description
								size_hint_y: .25
								cursor_blink: False
								background_color: [0,0,0,0]
								foreground_color: [1,1,1,1]
								multiline: True
								font_size: 12
								readonly: True


					AccordionItem:
						title: 'custom'
						orientation: 'vertical'
			AccordionItem:
				title: 'nmap firewalk'
				id: item_firewall
				orientation: 'vertical'
			AccordionItem:
				title: 'atomic firewalk'
				id: item_atomic_firewalk
				orientation: 'vertical'
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
								id: cci_action_prev
								title: 'king console'
								with_previous: False
								on_press: root._on_full_screen()
								app_icon: 'king-console32.png'
							ActionButton:
								text: 'history'
								on_press: app._on_view_manager()
							ActionButton:
								text: 'back'
								on_press: app._manip_extended_window( root )
					Carousel:
                        id: transport_carousel_id
                        direction: 'right'
                        GridLayout:
                            orientation: 'horizontal'
                            id: console_grid
                            cols: 1
                            Label:
                            	text: 'caveat emptor => Post hoc ergo propter hoc'
                            	color: [ 1, 0 , 0 , 1]
								font_size: 16
"""
,
					   'nmap_firewalk_view' :
"""
BoxLayout:
	orientation: 'vertical'
	ScrollView:
		GridLayout:
			cols: 1
			orientation: 'horizontal'
			size_hint_y: None
			size: ( 400 ,800 )
			GridLayout
				orientation: 'horizontal'
				cols: 1
				Label:
					text: 'max retries: ' + '{0:}'.format( retry_slider.value )
				Slider:
					orientation: 'horizontal'
					id: retry_slider
					step: 1
					min: 1
					max: 5
					value: 1
				Switch:
					active: False
				Label:
					text: 'probe timeout(ms): ' + '{0:}'.format( probe_slider.value )
				Slider:
					orientation: 'horizontal'
					id: probe_slider
					step: 20
					min: 20
					max: 800
					value: 400
				Switch:
					active: False
				Label:
					text: 'recv timeout(ms): ' + '{0:}'.format( probe_recv_slider.value )
				Slider:
					orientation: 'horizontal'
					id: probe_recv_slider
					step: 20
					min: 20
					max: 800
					value: 400
				Switch:
					active: False
				Label:
					text: 'max ports(-1=all): ' + '{0:}'.format( max_probe_slider.value )
				Slider:
					orientation: 'horizontal'
					id: max_probe_slider
					step: 1
					min: -1
					max: 500
					value: -1
				Switch:
					active: False
				Label:
					text: 'resource metric ip:'
				TextInput:
					text: 'cci-aws-1'
					id: ip_input_metric
					cursor_blink: True
					readonly: False
					multiline: True
				Button:
					id: do_firewalk_btn
					text: 'execute firewalk'
					background_color: [0,0,0,0]
					color: [1,0,0,1]


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

