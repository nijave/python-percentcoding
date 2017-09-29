#!/usr/bin/env python

import string
from percentcoding.cext import Codec

URI_UNRESERVED = string.ascii_uppercase + string.ascii_lowercase + string.digits + "-_.~"
URI_RESERVED = "!*'();:@&=+$,/?#[]"
URI_SAFE = ''.join( set([c for c in URI_UNRESERVED]) - set([c for c in URI_RESERVED]) )
URI_SAFE_FORM = URI_SAFE+'+'

urlcoding = Codec(URI_SAFE)
urlpluscoding = Codec(URI_SAFE_FORM)

def quote(s):
  global urlcoding
  return urlcoding.encode(s)

def quote_default(s, default='-'):
  if s is None:
    return default
  return quote(s)

def unquote(s):
  global urlcoding
  return urlcoding.decode(s)

def quote_plus(s):
  global urlpluscoding
  return urlpluscoding.encode(s.replace(" ","+"))

def unquote_plus(s):
  global urlpluscoding
  return urlpluscoding.decode(s.replace("+"," "))

