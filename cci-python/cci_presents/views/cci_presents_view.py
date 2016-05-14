#!/usr/bin/env python

"""
    cci_presents
    ~~~~~~


   william K. Johnson 2016
"""

import os
# from contextlib import closing
import sqlite3
from flask import Flask ,\
                  request , \
                  session , \
                  g ,\
                  redirect ,\
                  url_for ,\
                  abort , \
                  render_template ,\
                  flash , \
                  blueprints ,\
                  jsonify
from datetime import date
from cci_presents import application


def page_not_found( e , **kargs) :
    return render_template('404.html'), 404

def internal_server_error_t( e , **kargs ) :
    return render_template('500.html'), 500

def index_t( **kargs ):
    return render_template( 'home.html' )

def services_t( *kargs ):
    return render_template( 'services.html' )

def about_t( **kargs )  :
    """function to render the homepage"""
    return render_template( 'about.html' )

def about_pdf_t( **kargs )  :
    """function to render the homepage"""
    return render_template( 'viewer.html' )

def more_t( **kargs )  :
    """function to render more"""
    return render_template( 'learn_more_1.html' ,
                             topic = 'more_%s_inc.html' % kargs['tp'] ,
                             topic_name =  kargs['tp']  )
def cci_dev_t( **kargs )  :
    """function to render the homepage"""
    return render_template( 'domain.html' ,
                            server = kargs['serv'] )

def portfolio_t( **kargs )  :
    """function to render the portfolio"""
    return render_template( 'portfolio-4-col.html' ,
                            moniker = kargs['folio'] )



