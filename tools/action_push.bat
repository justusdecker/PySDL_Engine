git add -A
WScript.exe ./tools/get_current_commit_msg.vbs
git log --pretty=format:%%h -n 1 > ./tools/hash.i
python ./tools/easy_commit.py
set /p msg=<./tools/cmtmsg.i
set /p hsh=<./tools/hash.i


git commit -m "%msg%%hsh%"
git push