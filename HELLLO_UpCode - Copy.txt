#!/bin/bash

# Kiểm tra xem thư mục hiện tại đã được khởi tạo git chưa
if [ ! -d .git ]; then
  # Nếu chưa khởi tạo, thực hiện git init
  git init
fi

# URL của remote repository
remote_url="https://github.com/tranHaoPhong/HELLLO.git"

# Kiểm tra xem remote repository đã tồn tại hay chưa
if ! git remote -v | grep -q "origin.*$remote_url"; then
  # Nếu chưa tồn tại, thêm remote repository
  git remote add origin $remote_url
fi

# Thêm tất cả các tệp vào git
git add .

# Commit với thông báo "PHONGOOGLE"
git commit -m "PHONGOOGLE"

# Push lên origin master (lần đầu tiên)
git push -u origin master

# In thông báo khi hoàn thành
echo "Hoàn thành!"
