import managers
from api_helper import *

@error_handler
def main():
    try:
        obj = self.loads(request.arguments.get('xml_data'))
        result = managers.engine.wysiwyg(obj, self)
        write_response(result)

    except Exception as e:
        debug(str(e))
        raise

main()
