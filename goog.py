import gflags
import httplib2
import urllib2
import json

from datetime import datetime


from apiclient.discovery import build
from oauth2client.file import Storage
from oauth2client.client import OAuth2WebServerFlow
from oauth2client.tools import run
# Returns json response of weather forecast
def getWeatherCondition(city) :

    try :
        url = "http://openweathermap.org/data/2.1/forecast/city?q="
        url += city
        req = urllib2.Request(url)
        response=urllib2.urlopen(req)
    except Exception :
        print("Weather response error")
    return json.loads(response.read())

    # return json.dumps(response.read(), sort_keys=True,indent=4, separators=(',', ': '))


FLAGS = gflags.FLAGS

# Set up a Flow object to be used if we need to authenticate. This
# sample uses OAuth 2.0, and we set up the OAuth2WebServerFlow with
# the information it needs to authenticate. Note that it is called
# the Web Server Flow, but it can also handle the flow for native
# applications
# The client_id and client_secret can be found in Google Developers Console
FLOW = OAuth2WebServerFlow(
    client_id='498610804449-p6ra03o5aoe83fia54fn4kalgu65vjd6.apps.googleusercontent.com',
    client_secret='iNwld8fTWvT5Q_3MkiMcYPaD',
    scope='https://www.googleapis.com/auth/calendar',
    user_agent='SmartMirrorPrototypeTest')

# To disable the local server feature, uncomment the following line:
# FLAGS.auth_local_webserver = False

# If the Credentials don't exist or are invalid, run through the native client
# flow. The Storage object will ensure that if successful the good
# Credentials will get written back to a file.
storage = Storage('calendar.dat')
credentials = storage.get()
if credentials is None or credentials.invalid == True:
    credentials = run(FLOW, storage)

# Create an httplib2.Http object to handle our HTTP requests and authorize it
# with our good Credentials.
http = httplib2.Http()
http = credentials.authorize(http)

# Build a service object for interacting with the API. Visit
# the Google Developers Console
# to get a developerKey for your own application.
service = build(serviceName='calendar', version='v3', http=http,
       developerKey='AIzaSyCJzAKMyoak2xemkY41yYpc4-UGjQ0EO84')


#Let's see if we can't actually get the calendar items now
page_token = None
while True:
    events = service.events().list(calendarId='primary', pageToken=page_token).execute()
    data = getWeatherCondition("Boulder")
    print "Calender events:"
    for event in events['items']:
        if event.get('reminders').get('overrides'):
            print "\t-> ",event['summary'],"\n\t\tstarting at",event.get('start','').get('dateTime',''),"to" ,event.get('end','').get('dateTime','') \
            ,"\n\t\twith reminders: ", event['reminders']['overrides'][0].get('minutes'),"min before by",event['reminders']['overrides'][0].get('method')
        elif event.get('start').get('dateTime'):
            print "\t-> ",event['summary'],"\n\t\tstarting at",event.get('start','').get('dateTime',''),"to" ,event.get('end','').get('dateTime','')
        else:
            print "\n\t-> ",event['summary'],"\n"

    print data["city"]["name"]+"'s","weather forecast for",data["list"][0]["dt_txt"],"is",data["list"][0]["weather"][0]["description"]

    page_token = events.get('nextPageToken')
    if not page_token:
        break
