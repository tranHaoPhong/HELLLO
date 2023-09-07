from github import Github
import os

# Thay thế bằng YOUR_ACCESS_TOKEN
access_token = "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"

# Nhập tên repository từ người dùng
repository_name = input("Nhập tên repository trên GitHub: ")

# Thư mục hiện tại chứa code bạn muốn đăng lên
code_directory = os.path.dirname(os.path.realpath(__file__))

# Tạo kết nối tới GitHub bằng YOUR_ACCESS_TOKEN
g = Github(access_token)

# Lấy repository bạn muốn đăng code lên
repo = g.get_user().get_repo(repository_name)

# Duyệt qua tất cả các tệp trong thư mục
for root, dirs, files in os.walk(code_directory):
    for file in files:
        file_path = os.path.join(root, file)

        # Kiểm tra xem tên tệp có là script chính không
        if file == "UpCodeGitHub.py":
            continue  # Loại trừ script chính

        # Đọc nội dung của tệp
        with open(file_path, 'r', encoding='utf-8') as f:
            code_content = f.read()

        # Lấy tên tệp gốc (không kèm đường dẫn)
        file_name = os.path.basename(file_path)

        # Tạo một commit và đẩy code lên GitHub
        commit_message = f"PHONGOOGLE"
        try:
            repo.create_file(file_name, commit_message, code_content)
            print(f"Tệp {file_name} đã được đăng lên GitHub thành công!")
        except Exception as e:
            print(f"Có lỗi xảy ra khi tải lên tệp {file_name}: {str(e)}")
