import os
from gtts import gTTS

MODULE_COUNT = 4  # Number of modules
TEXT_TEMPLATE = "module{}.txt"
AUDIO_TEMPLATE = "module{}.mp3"

def convert_module_to_audio(index):
    text_file = TEXT_TEMPLATE.format(index)
    audio_file = AUDIO_TEMPLATE.format(index)

    if not os.path.exists(text_file):
        print(f"⚠️ {text_file} not found. Skipping...")
        return

    try:
        with open(text_file, "r", encoding="utf-8") as f:
            text = f.read().strip()

        if not text:
            print(f"⚠️ {text_file} is empty. Skipping...")
            return

        tts = gTTS(text)
        tts.save(audio_file)
        print(f"✅ Finished module {index} → {audio_file}")

    except Exception as e:
        print(f"❌ Error converting module {index}: {e}")

def main():
    print("🔊 Starting batch text to audio conversion...")
    for i in range(2, MODULE_COUNT + 1):
        convert_module_to_audio(i)

if __name__ == "__main__":
    main()
