import os

def count_hpp_lines(directory):
    total_lines = 0

    for filename in os.listdir(directory):
        if filename.endswith('.hpp'):
            file_path = os.path.join(directory, filename)
            try:
                with open(file_path, 'r', encoding='utf-8') as file:
                    lines = file.readlines()
                    total_lines += len(lines)
            except Exception as e:
                print(f"Error reading file {file_path}: {e}")

    return total_lines

if __name__ == "__main__":
    current_directory = os.getcwd()
    total = count_hpp_lines(current_directory)
    print(f"Total number of lines in .hpp files: {total}")
