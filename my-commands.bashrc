alias start-both='(cd /home/misc/work/e7na/Car-control && { node index.js & pipenv run python joystic.py; } )'
alias kill-both="pkill -9 -f 'python.*joystic.py' & pkill -9 -f 'node.*index.js'"
