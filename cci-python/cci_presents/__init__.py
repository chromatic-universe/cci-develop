#!/usr/bin/env python

from flask import Flask

# create our application
application = Flask( __name__ )

# Load the configuration settings
#application.config.from_object( 'cci_presents.default_settings' )

# from views.cci_pesents import index

# application.register_blueprint( index )
"""
from .views.motor import motor
from .views.universaltaxdist import universaltaxdist

# main website:
application.register_blueprint( home )
# motor neuron app:
application.register_blueprint(motor)
# universal taxonomic distributions app:
application.register_blueprint(universaltaxdist)
"""
#import cci_presents.views

