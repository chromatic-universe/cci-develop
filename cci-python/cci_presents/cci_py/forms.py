#forms.py william k. johnson 2016


from flask.ext.wtf import Form
from wtforms import TextField ,\
                    TextAreaField ,\
                    SubmitField , \
                    validators , \
                    ValidationError
import doctest
import unittest

class email_contact_form( Form ) :
        """
        email contact form
        """

        name = TextField( "name" , [validators.DataRequired( 'please enter your name')] )
        email = TextField( "email"  ,  [validators.DataRequired( 'please enter your email address') , validators.Email()] )
        subject = TextField( "subject" , [validators.DataRequired( 'please enter subject')] )
        message = TextAreaField( "message" , [validators.Required( 'please enter message body')]  )
        submit = SubmitField( "send" )