import sys
import os
import re
from PyPDF2 import PdfReader
from gtts import gTTS

def extract_text_from_pdf(pdf_path):
    reader = PdfReader(pdf_path)
    return "\n".join([page.extract_text() for page in reader.pages if page.extract_text()])

def clean_text(text):
    cleaned_lines = []

    for line in text.splitlines():
        # Skip lines with copyright, all rights reserved, or "source:"
        if re.search(r'\bcopyright\b', line, re.IGNORECASE):
            continue
        if re.search(r'\discover the palm beaches\b', line, re.IGNORECASE):
            continue
        if re.search(r'all rights reserved', line, re.IGNORECASE):
            continue
        if re.search(r'\bsource:', line, re.IGNORECASE):
            continue

        # Remove parenthetical content
        line = re.sub(r'\([^)]*\)', '', line)

        # Remove all types of URLs
        line = re.sub(r'https?://\S+|www\.\S+|\b\w+\.\w+/\S*', '', line)

        # Remove excessive internal spaces and strip
        line = re.sub(r'\s+', ' ', line).strip()

        if line:
            cleaned_lines.append(line)

    return '\n'.join(cleaned_lines)

def save_text_to_file(text, output_path):
    with open(output_path, 'w', encoding='utf-8') as f:
        f.write(text)
    print(f"📝 Cleaned text saved to {output_path}")

def convert_text_to_audio(text, output_audio_path):
    tts = gTTS(text)
    tts.save(output_audio_path)
    print(f"🔊 Audio saved to {output_audio_path}")

def main(pdf_path, output_text_path="output.txt", output_audio_path="output.mp3"):
    if not os.path.isfile(pdf_path):
        print("❌ File does not exist.")
        return

    print(f"📖 Reading PDF: {pdf_path}")
    raw_text = extract_text_from_pdf(pdf_path)
    cleaned_text = clean_text(raw_text)

    save_text_to_file(cleaned_text, output_text_path)

    proceed = input("✅ Review the text file. Type 'y' to generate audio: ").strip().lower()
    if proceed == 'y':
        convert_text_to_audio(cleaned_text, output_audio_path)
    else:
        print("❌ Aborted audio conversion.")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python pdf_to_audio_clean.py <path_to_pdf> [text_output] [audio_output]")
    else:
        pdf_path = sys.argv[1]
        text_path = sys.argv[2] if len(sys.argv) > 2 else "output.txt"
        audio_path = sys.argv[3] if len(sys.argv) > 3 else "output.mp3"
        main(pdf_path, text_path, audio_path)
