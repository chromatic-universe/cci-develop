# kv resources
const_app_discovery_ids = {
					   'app_discovery_extended_screen' :
"""


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
                title: 'geography'
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
}
