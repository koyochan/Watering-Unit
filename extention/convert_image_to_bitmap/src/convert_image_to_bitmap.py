from PIL import Image

def convert_image_to_bitmap(input_image_path, output_header_path, array_name="image_data"):
    # 画像を開く
    img = Image.open(input_image_path)

    # 画像を135x240ピクセルにリサイズ
    img = img.resize((135, 240))

    # 画像を1ビットビットマップ形式に変換
    img = img.convert("1")

    # ビットマップデータを取得
    bitmap_data = img.tobytes()

    # ヘッダーファイルに書き込む
    with open(output_header_path, 'w') as header_file:
        header_file.write(f"const unsigned char {array_name}[] PROGMEM = {{\n")
        for i, byte in enumerate(bitmap_data):
            header_file.write(f"0x{byte:02X}")
            if i < len(bitmap_data) - 1:
                header_file.write(", ")
            if (i + 1) % 12 == 0:  # 12バイトごとに改行
                header_file.write("\n")
        header_file.write("\n};\n")

if __name__ == "__main__":
    # 入力画像のパスと出力ヘッダーファイルのパス
    input_image_path = "../images/tabechan.jpeg"
    output_header_path = "../../lib/image.h"

    # 画像を変換してヘッダーファイルに書き込む
    convert_image_to_bitmap(input_image_path, output_header_path)