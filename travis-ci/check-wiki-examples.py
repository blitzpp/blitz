#!/usr/bin/python3

def retrieve_from_wiki():
  import git, tempfile, shutil, os
  try:
    t = tempfile.mkdtemp()
    git.Repo.clone_from('https://github.com/blitzpp/blitz.wiki.git', t, branch='master', depth=1)
    with open(os.path.join(t, 'Features.md'), 'r') as f:
      return f.readlines()
  finally:
    shutil.rmtree(t)
data = retrieve_from_wiki()
print('--', 'read', len(data), 'line[s]')


def parse_the_tags(lines):
  import re
  from collections import defaultdict
  p = re.compile(r'<!---[a-z]{3}-->')
  curr = None
  last = None
  data = []
  for line in lines:
    m = p.match(line)
    if m is not None:
      last = curr
      curr = line[5:8]
      if curr == last: continue
      if curr == 'src': data.append(defaultdict(list))
    elif curr is not None:
      if line[0:3] != '```': data[-1][curr].append(line)
  return data
data = parse_the_tags(data)
print('--', 'read', len(data), 'block[s]')


def compile_and_check(examples):
  import tempfile, shutil, os, subprocess
  path = os.getcwd()
  errcnt = 0
  for exno, example in enumerate(examples):
    try:
      # writing src to example.cpp
      t = tempfile.mkdtemp()
      with open(os.path.join(t, 'example.cpp'), 'w') as f:
        f.writelines(example['src'])
      
      # executing commands from cmd
      print('--', 'compiling example', exno)
      os.chdir(t)
      with open(os.path.join(t, 'output.log'), 'w') as f:
        for cmd in example['cmd']:
          subprocess.call(cmd[2:].strip().split(' '), stderr=subprocess.STDOUT, stdout=f)

      # comparing with out
      with open(os.path.join(t, 'output.log'), 'r') as f:
        for i, line in enumerate(f.readlines()):
          if example['out'][i] != line:
            print('--', 'error')
            errcnt += 1

    finally:
      os.chdir(path)
      shutil.rmtree(t)
  return errcnt
nerr = compile_and_check(data)

import sys
if nerr != 0: sys.exit(1)
