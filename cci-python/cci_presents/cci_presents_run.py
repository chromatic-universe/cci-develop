# cci_presents_run.py william k. johnson 2016

#!/usr/bin/env python

import sys , \
       os , \
       doctest , \
       unittest
import redis
import gevent
from flask import Flask ,\
                  request , \
                  flash , \
                  render_template ,\
                  redirect
from flask.ext.googlemaps import GoogleMaps
from flask.ext.mail import Message, Mail
from flask_sockets import Sockets


# cci
import views.cci_presents_views as cci
from cci_py.cci_forms import email_contact_form , \
                             customer_stream_form
from cci_py.cci_mini_im import cci_base_chat_server
import cci_utils.cci_io_tools as io

#
# application static globals
#
# flask application
application = Flask( __name__ )
# googlemaps
GoogleMaps( application )
# mail
mail = Mail()
# web sockets
sockets = Sockets( application )
# base pubsub
cci_stream = None
# redis
redis_config =  {
                  'channel' : 'chat' ,
                  'url' : '127.0.0.1:6379'
                }
redis = redis.from_url( redis_config['url'] )

application.config['SECRET_KEY'] = 'the original corny snaps!'

# mail config
application.config["MAIL_SERVER"] = "smtp.gmail.com"
application.config["MAIL_PORT"] = 465
application.config["MAIL_USE_SSL"] = True
application.config["MAIL_USERNAME"] = 'chromaticuniverse79@gmail.com'
application.config["MAIL_PASSWORD"] = 'Argentina123'
mail.init_app( application )

# image rotation
portfolio_images = { 'c++' : 'game.jpg' ,
                     'python' : 'shutter.jpg' ,
                     'objectpascal' : 'uvm.png' ,
                     'c99' : 'drought.jpg' ,
                     'rpc' : 'ocean.jpg' ,
                     'api' : 'materials.jpg' ,
                     'messaging' : 'materials.jpg' ,
                     'interop' : 'materials.jpg'}
server_to_profile = { ''}


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
        return  cci.about_t()


# -----------------------------------------------------
@application.route( '/more/<topic>' )
def more( topic )  :
        """
        more data about william k. page

        :return:
        """

        return  cci.more_t( tp = topic ,
                            image = portfolio_images[topic] )


# -----------------------------------------------------
@application.route( '/about/pdf/<pd>' )
def about_pdf( pd )  :
        """
        more data about william k. page

        :return:
        """

        return  cci.about_pdf_t( ps = pd )

# -----------------------------------------------------
@application.route( '/sidebar' )
def sidebar()  :

    return render_template( 'sidebar.html' )

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

        if moniker == 'github' :
            return redirect( 'https://github.com/chromatic-universe' )
        else :
            return  cci.portfolio_t(  folio = moniker ,
                                      image = portfolio_images[moniker] )


# -----------------------------------------------------
@application.route( '/contact' , methods=['GET', 'POST'] )
def contact() :
        """
        contact william k. page

        :return:
        """

        form = email_contact_form()
        if request.method == 'POST' :
            if not form.validate() :
              flash('all fields are required.')
              return  cci.contact_t( form = form ,
                                     success=False ,
                                     name = '' )
            else :
              # compose message
              msg = Message( form.subject.data ,
                              sender= application.config["MAIL_USERNAME"] ,
                              recipients=['chromaticuniverse80@gmail.com'])
              msg.body = """
                          From: %s <%s>
                          %s
                          """ % ( form.name.data ,
                                  form.email.data ,
                                  form.message.data )
              # send message
              mail.send( msg )

              return  cci.contact_t( form = form ,
                                     success=True ,
                                     name = form.name.data )
        elif request.method == 'GET' :
            return  cci.contact_t( form = form ,
                                   success =False ,
                                   name = '' )



# -----------------------------------------------------
@application.route( '/faq' )
def faq()  :
        """
        faq william k. page

        :return:
        """

        return  cci.faq_t()


# -----------------------------------------------------
@application.route( '/customer_stream' , methods=['GET', 'POST'] )
def customer_stream()  :
        """
        stream customers william k. page

        :return:
        """
        form = customer_stream_form()
        if request.method == 'POST' :
            return  cci.customer_stream_t( success = False ,
                                           form = form )
        elif request.method == 'GET' :
            return  cci.customer_stream_t( success = False ,
                                           form = form )

# ------------------------------------------------------
@sockets.route( '/submit' )
def inbox( ws ) :
        """
        receives incoming chat messages, inserts them into redis
        :param ws:
        :return:
        """
        cci_stream.logger.info( 'submit' )
        while not ws.closed:
            # sleep to prevent *constant* context-switches.
            gevent.sleep(0.1)
            message = ws.receive()

            if message:
                cci_stream.logger.info( u'inserting message: {}'.format(message))
                cci_stream.redis.publish( redis_config['channel'] , message)

# ---------------------------------------------------------
@sockets.route('/receive')
def outbox(ws):
        """
        sends outgoing chat messages, via chat server
        """
        cci_stream.logger.info( 'receive' )
        cci_stream.register( ws )

        while not ws.closed:
            # context switch while chat server  is running in the background.
            gevent.sleep( 0.1 )



# ------------------------------------------------------
if __name__ == '__main__' :

        if not redis :
            raise Exception( 'redis publish subscribe interface unavailable....' )

        # bring up our pubsub interface
        try :
             # web sockets
             cci_stream  = cci_base_chat_server( red = redis  ,
                                                 web_sockets = sockets ,
                                                 flask_app = application )
             cci_stream.logger.info( "instantiated redis endpoint.....")

             # start
             cci_stream.start()
             cci_stream.logger.info( "started stream server....." )



        except ValueError as err :
             raise Exception( 'could not initialize cci_presents...' + err.message )

        application.run( debug=True )



