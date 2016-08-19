from flask import Flask

app = Flask( __name__ , template_folder='./templates')

class mongo_no_resource_exception( Exception ):
    pass
