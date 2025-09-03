git add -A
./tools/get_current_commit_msg.vbs
git log --pretty=format:%%h -n 1 > ./tools/hash.i
python ./tools/easy_commit.py
set /p ver=<./tools/cmtmsg.i
set /p hsh=<./tools/hash.i
set /p msg=<./tools/cm.i
git commit -m "%ver%:%hsh% - %msg%"
git push