#!/bin/bash

# Kiểm tra xem thư mục hiện tại đã được khởi tạo git chưa
if [ ! -d .git ]; then
  # Nếu chưa khởi tạo, thực hiện git init
  git init
fi

# Thêm remote repository
git remote add origin https://github.com/tranHaoPhong/HELLLO.git

# Kiểm tra remote repository đã tồn tại hay chưa
if ! git remote -v | grep -q "origin.*https://github.com/tranHaoPhong/HELLLO.git"; then
  echo "Lỗi: Không thể thêm remote repository."
  exit 1
fi

# Thêm tất cả các tệp vào git
git add .

# Commit với thông báo "PHONGOOGLE"
git commit -m "PHONGOOGLE"

# Push lên origin master (lần đầu tiên)
git push -u origin master

# In thông báo khi hoàn thành
echo "Hoàn thành!"
