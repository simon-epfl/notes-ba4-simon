#!/usr/bin/env python3
import os
import re
import shutil
from pathlib import Path

def find_markdown_files():
    markdown_files = []
    for root, _, files in os.walk('.'):
        for file in files:
            if file.endswith('.md'):
                markdown_files.append(os.path.join(root, file))
    return markdown_files

def find_image_files():
    image_files = {}
    for root, _, files in os.walk('.'):
        for file in files:
            if file.lower().endswith(('.png', '.jpg', '.jpeg', '.gif', '.bmp')):
                image_files[file] = os.path.join(root, file)
    return image_files

def find_image_references(markdown_file):
    with open(markdown_file, 'r', encoding='utf-8') as f:
        content = f.read()
    
    pattern = r'!\[\[([^|\]]+)(?:\|([^\]]+))?\]\]'
    matches = re.finditer(pattern, content)
    
    image_refs = []
    for match in matches:
        image_path = match.group(1)
        dimensions = match.group(2) or ""
        image_refs.append((image_path, dimensions, match.group(0)))
    
    return image_refs

def organize_images():
    markdown_files = find_markdown_files()
    image_files = find_image_files()
    
    for md_file in markdown_files:
        md_dir = os.path.dirname(md_file)
        assets_dir = os.path.join(md_dir, 'assets')
        
        image_refs = find_image_references(md_file)
        
        if not image_refs:
            continue
            
        os.makedirs(assets_dir, exist_ok=True)
        
        for image_path, dimensions, full_match in image_refs:
            image_name = os.path.basename(image_path)
            
            if image_name in image_files:
                source_path = image_files[image_name]
                target_path = os.path.join(assets_dir, image_name)
                
                shutil.move(source_path, target_path)
                
                new_ref = f'![[assets/{image_name}{"" if not dimensions else "|" + dimensions}]]'
                with open(md_file, 'r', encoding='utf-8') as f:
                    content = f.read()
                content = content.replace(full_match, new_ref)
                with open(md_file, 'w', encoding='utf-8') as f:
                    f.write(content)
                print(f"Moved {image_name} to {assets_dir}")

if __name__ == '__main__':
    organize_images() 
