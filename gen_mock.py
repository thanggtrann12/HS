import re
import os
import shutil
class MockFileGenerator:
    def __init__(self, header_file_path, mock_file_path, mock_class_name, base_class_name, base_path):
        self.header_file_path = header_file_path
        self.mock_file_path = mock_file_path
        self.mock_class_name = mock_class_name
        self.base_class_name = base_class_name
        self.base_path = base_path

    def generate_mock_file(self):
        mock_file_content = ""
        
        # Include guard
        header_guard = f"{self.mock_class_name}_H"
        mock_file_content += f"#ifndef {header_guard.upper()}\n#define {header_guard.upper()}\n\n#include \"gtest/gtest.h\"\n#include \"gmock/gmock.h\"\n"

        # Begin mock class declaration
        relative_path = os.path.relpath(self.header_file_path, self.base_path).replace("\\", "/")
        mock_file_content += f'#include "{relative_path}"\n'
        mock_file_content += f"\n// Mock class for {self.mock_class_name}\n"
        mock_file_content += f"class {self.mock_class_name} : public {self.base_class_name} {{\npublic:\n"

        # Process each line in the header file and generate mock declarations
        with open(self.header_file_path, 'r', encoding='utf-8') as header_file:
            for line in header_file:
                line = line.strip()

                # Use regular expression to match the function declaration in the header file
                match = re.match(r"(.+?)\s+(\w+)\s*\((.*?)\)\s*;", line)

                if match:
                    return_type, method_name, args_part = match.groups()

                    # Split arguments and specs
                    args = list(map(str.strip, args_part.split(',')))

                    # Add commas back to the args
                    args_with_commas = ', '.join(args)

                    # Generate mock method declaration inside the mock class
                    mock_declaration = f"    MOCK_METHOD({return_type}, {method_name}, ({args_with_commas}));"
                    mock_file_content += mock_declaration + "\n"

        # End mock class declaration
        mock_file_content += "};\n"
        # Include guard
        mock_file_content += f"#endif // {header_guard.upper()}\n"
        # Append the generated mock content to the mock file
        self.append_before_line(self.mock_file_path, mock_file_content)

    def append_before_line(self, file_path, text_to_append):
# Create the folder path from the current directory

        if not os.path.exists(file_path):
            with open(file_path, 'w', encoding='utf-8') as new_file:
                new_file.write(text_to_append)
            return

        with open(file_path, 'r', encoding='utf-8') as file:
            lines = file.readlines()

        # Find the index of the target line
        target_index = -1
        for i, line in enumerate(lines):
            if "#endif" in line:
                target_index = i
                break

        # If the target line is found, insert the new text before it
        if target_index != -1:
            lines.insert(target_index, text_to_append + '\n')

            # Write the modified content back to the file
            with open(file_path, 'w', encoding='utf-8') as file:
                file.writelines(lines)

base_path = os.path.abspath(os.getcwd())
file_paths = [
    base_path+"/inc/Player/Player.h",
    base_path+"/inc/UI/Ui.h",
    base_path+"/inc/Hero/Hero.h",
    base_path+"/inc/Card/CardFactory.h",
    base_path+"/inc/Card/Card.h",
    base_path+"/inc/MySocket/MySocket.h",
    base_path+"/inc/Engine/Engine.h",
    base_path+"/inc/CardManager/CardManager.h",
    base_path+"/inc/assets/HeroData.h",
    base_path+"/inc/assets/CardData.h"
]
for filename in os.listdir(base_path+"\\utest\\mock"):
    file_path = os.path.join(base_path+"\\utest\\mock", filename)
    try:
        if os.path.isfile(file_path) or os.path.islink(file_path):
            os.unlink(file_path)
        elif os.path.isdir(file_path):
            shutil.rmtree(file_path)
    except Exception as e:
        print('Failed to delete %s. Reason: %s' % (file_path, e))
mock_folder_path = base_path+ "/utest/mock/"
os.makedirs(mock_folder_path, exist_ok=True)
# folder_path = os.path.join(os.getcwd(), "utes\mock\\")
# [shutil.rmtree(folder_path) for folder_path in [d for d in os.listdir() if os.path.isdir(d)]]
for file_path in file_paths:
    result = ""
    header_file_path = file_path
    start_index = header_file_path.rfind('/')
    end_index = header_file_path.rfind('.', start_index + 1)

    if start_index != -1 and end_index != -1:
        result = header_file_path[start_index + 1:end_index]

    mock_file_path = os.path.join(mock_folder_path, f"mock_{result}.h")
    mock_class_name = f"Mock_{result}"
    base_class_name = result

    mock_generator = MockFileGenerator(header_file_path, mock_file_path, mock_class_name, base_class_name, base_path+"/inc/")
    mock_generator.generate_mock_file()
