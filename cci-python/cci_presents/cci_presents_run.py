# cci_presents_run.py william k. johnson 2016

#!/usr/bin/env python

import sys , \
       os , \
       doctest , \
       unittest
from flask import Flask
from flask.ext.googlemaps import GoogleMaps

import views.cci_presents_view as cci

application = Flask( __name__ )
GoogleMaps( application )
application.config['SECRET_KEY'] = 'the original corny snaps!'

portfolio_images = { 'c++' : 'game.jpg' ,
                     'python' : 'shutter.jpg' ,
                     'objectpascal' : 'uvm.png' ,
                     'c99' : 'materials.jpg' }


# -----------------------------------------------------
@application.route('/')
def index()  :
        """
        index - root url
        :return:
        """
        return cci.index_t()
# -----------------------------------------------------
@application.errorhandler( 404 )
def page_not_found( e ) :
        """
        not found - return error obj
        :param e:
        :return:
        """
        return cci.page_not_found( e )
# -----------------------------------------------------
@application.errorhandler( 500)
def internal_server_error(e) :
        """
        server error , is not handled during debug

        :param e:
        :return:
        """
        return cci.internal_server_error_t( e )
# -----------------------------------------------------
@application.route( '/services' )
def services() :
        """
        services page

        :return:use regex flask url
        """
        return cci.services_t()
# -----------------------------------------------------
@application.route( '/about' )
def about()  :
        """
        about page

        :return:
        """
        return  cci.about_t();
# -----------------------------------------------------
@application.route( '/more/<topic>' )
def more( topic )  :
        """
        more data about william k. page

        :return:
        """

        return  cci.more_t( tp = topic )
# -----------------------------------------------------
@application.route( '/about/pdf/<pd>' )
def about_pdf( pd )  :
        """
        more data about william k. page

        :return:
        """

        return  cci.about_pdf_t( ps = pd )
# -----------------------------------------------------
@application.route( '/domain/<server>' )
def cci_dev( server )  :
        """
        domain dev servers

        :param: server
        :return:
        """

        return  cci.cci_dev_t(  serv = server )
# -----------------------------------------------------
@application.route( '/portfolio/<moniker>' )
def portfolio( moniker )  :
        """
        portfolio

        :param: moniker
        :return:
        """

        return  cci.portfolio_t(  folio = moniker ,
                                  image = portfolio_images[moniker] )

# -----------------------------------------------------
@application.route( '/contact' )
def contact()  :
        """
        contact william k. page

        :return:
        """

        return  cci.contact_t()
# -----------------------------------------------------
@application.route( '/faq' )
def faq()  :
        """
        faq william k. page

        :return:
        """

        return  cci.faq_t()

# -----------------------------------------------------
@application.route( '/customer_stream' )
def customer_stream()  :
        """
        stream customers william k. page

        :return:
        """

        return  cci.customer_stream_t()


# -------------------------------------------------
if __name__ == '__main__':

        application.run( debug=True )



