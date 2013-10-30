Flags = [
    '-g',
    '-std=c++11',
    '-Wall',
    '-pedantic',
]

def FlagsForFile( filename ):
  return {
    'flags': Flags,
    'do_cache': True
  }
