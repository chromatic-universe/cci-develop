#forms.py william k. johnson 2016


from flask.ext.wtf import Form
from wtforms import TextField ,\
                    StringField , \
                    TextAreaField ,\
                    SubmitField , \
                    validators , \
                    ValidationError
import doctest
import unittest

# ------------------------------------------------------------------
class email_contact_form( Form ) :
        """
        email contact form
        """

        name = StringField( "name" , [validators.DataRequired( 'please enter your name')] )
        email = StringField( "email"  ,  [validators.DataRequired( 'please enter your email address') , validators.Email()] )
        subject = StringField( "subject" , [validators.DataRequired( 'please enter subject')] )
        message = TextAreaField( "message" , [validators.DataRequired( 'please enter message body')]  )
        submit = SubmitField( "send" )

# ------------------------------------------------------------------
class customer_stream_form( Form ) :
        """
        form for customer publish/subscribe
        """

        customer_handle =  StringField( "handle" , [validators.DataRequired( 'please enter your handle')] )
        email = StringField( "email"  ,  [validators.DataRequired( 'please enter your email address') , validators.Email()] )
        message = TextAreaField( "message" , [validators.DataRequired( 'please enter message body')]  )
        submit = SubmitField( "publish" )
