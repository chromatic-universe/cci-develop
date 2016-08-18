from flask import Flask

app = Flask( __name__ )

class mongo_no_resource_ecxception( Exception ):
    pass
