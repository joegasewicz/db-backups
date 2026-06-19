sign:
	codesign \
      --force \
      --timestamp \
      --options runtime \
      --sign - \
      ./cmake-build-debug/db_backups