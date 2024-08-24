import numpy as np
import scipy.io.wavfile as wav
import pyaudio
import sys
import wave

def record_audio(output_wav_file, record_seconds=1, sample_rate=16000, chunk_size=1024):
    audio = pyaudio.PyAudio()

    # 録音ストリームの設定
    stream = audio.open(format=pyaudio.paInt16, channels=1,
                        rate=sample_rate, input=True,
                        frames_per_buffer=chunk_size)

    print("Recording...")
    frames = []

    for _ in range(int(sample_rate / chunk_size * record_seconds)):
        data = stream.read(chunk_size)
        frames.append(data)

    print("Finished recording.")
    stream.stop_stream()
    stream.close()
    audio.terminate()

    # WAVファイルに保存
    with wave.open(output_wav_file, 'wb') as wf:
        wf.setnchannels(1)
        wf.setsampwidth(audio.get_sample_size(pyaudio.paInt16))
        wf.setframerate(sample_rate)
        wf.writeframes(b''.join(frames))

def generate_tone_function(wav_file, output_file):
    # WAVファイルの読み込み
    sample_rate, data = wav.read(wav_file)
    
    if len(data.shape) > 1:
        # ステレオ音声の場合はモノラルに変換
        data = np.mean(data, axis=1)
    
    # 音のデータを16ビットにスケーリング
    data = data.astype(np.int16)

    # ヘッダーファイルに書き込む
    with open(output_file, 'w') as f:
        f.write("const uint16_t tone_data[] PROGMEM = {\n")

        # データを16ビット（2バイト）ごとに書き込む
        for i in range(0, len(data), 1):
            f.write(f"0x{data[i]:04X}, ")
            if (i + 1) % 8 == 0:
                f.write("\n")

        f.write("};\n\n")

if __name__ == "__main__":

    output_wav = "../output.wav"
    output_header = "../../lib/tone_data.h"

    # 録音
    record_audio(output_wav)

    # 録音した音声データをヘッダーファイルに変換
    generate_tone_function(output_wav, output_header)
    print(f"Tone function written to {output_header}")
