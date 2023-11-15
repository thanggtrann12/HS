import re
import os
class MockFileGenerator:
    def __init__(self, header_file_path, mock_file_path, mock_class_name, base_class_name, base_path):
        self.header_file_path = header_file_path
        self.mock_file_path = mock_file_path
        self.mock_class_name = mock_class_name
        self.base_class_name = base_class_name
        self.base_path = base_path

    def generate_mock_file(self):
        mock_file_content = ""
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

        # Append the generated mock content to the mock file
        self.append_before_line(self.mock_file_path, mock_file_content)

    def append_before_line(self, file_path, text_to_append):
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


base_path = "U:/C++_Tranining/HS"
file_paths = [
    base_path+"/inc/CardManager/CardManager.h",
    base_path+"/inc/CardManager/Hero.h",
    base_path+"/inc/GameEngine/GameEngine.h",
    base_path+"/inc/MySocket/MySocket.h",
    base_path+"/inc/GameUi/GameUi.h"
]

for file_path in file_paths:
    result = ""
    header_file_path = file_path
    start_index = header_file_path.rfind('/')
    end_index = header_file_path.rfind('.', start_index + 1)

    if start_index != -1 and end_index != -1:
        result = header_file_path[start_index + 1:end_index]

    mock_file_path = "U:/C++_Tranining/HS/UT/mock/mock.h"
    mock_class_name = f"Mock{result}"
    base_class_name = result

    mock_generator = MockFileGenerator(header_file_path, mock_file_path, mock_class_name, base_class_name, base_path+"/inc/")
    mock_generator.generate_mock_file()
