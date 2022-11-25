from pydrive.auth import GoogleAuth
from pydrive.drive import GoogleDrive
gauth = GoogleAuth()
gauth.LoadCredentialsFile("mycreds.txt")
if gauth.credentials is None:
    gauth.LocalWebserverAuth()
elif gauth.access_token_expired:
    gauth.Refresh()
else:
    gauth.Authorize()
gauth.SaveCredentialsFile("mycreds.txt")
drive = GoogleDrive(gauth)
folder_ID="輸入資料夾ID"
file1=drive.CreateFile({'parents':[{'kind':'drive#fileLink','id': folder_ID}]})
file1.SetContentFile("檔案名稱") 
file1.Upload()