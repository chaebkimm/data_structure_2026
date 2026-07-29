from pathlib import Path

week = '''Week 13: Graph Theory II (Traversal & Pathfinding)'''

def amalgamate_markdown(input_dir=".", output_file="combined_output.txt", preamble_text = ""):
    source_path = Path(input_dir).resolve()
    output_path = Path(output_file).resolve()
    
    file_count = 0
    
    with open(output_path, "w", encoding="utf-8") as outfile:
        # 1. Gather all markdown files and sort them
        all_files = sorted([f for f in source_path.rglob("*.md") if f.is_file()])
        
        # 2. Separate files in the root input directory vs subdirectories
        root_files = [f for f in all_files if f.parent == source_path and f.resolve() != output_path]
        sub_files = [f for f in all_files if f.parent != source_path and f.resolve() != output_path]
        
        # Combine lists to prioritize root directory files first, followed by subfolder files
        ordered_files = root_files + sub_files
        
        for file_path in ordered_files:
            relative_path = file_path.relative_to(source_path)
            
            # Write a visual header separator for each file
            outfile.write(preamble_text)
            outfile.write(f"\n\n<!-- BEGIN FILE: {relative_path} -->\n")
            outfile.write(f"# File: {relative_path}\n\n")
            
            try:
                content = file_path.read_text(encoding="utf-8")
                outfile.write(content)
                file_count += 1
                print(f"Added: {relative_path}")
            except Exception as e:
                print(f"Error reading {relative_path}: {e}")
                
            outfile.write("\n\n<!-- END FILE -->\n")
            
    print(f"\nFinished! Combined {file_count} Markdown file(s) into '{output_file}'.")

if __name__ == "__main__":
    amalgamate_markdown(input_dir=".", output_file="./prompt_toc.txt", preamble_text=f"""

generate the table of contents for {week}

, where,

"""
    )

    amalgamate_markdown(input_dir=".", output_file="./prompt_text.txt", preamble_text=f"""

generate the textbook contents for {week}

, where,

"""
    )
