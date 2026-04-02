def convert_to_seconds(minutes):
    seconds = minutes * 60
    return seconds

def main():
    minutes=int(input("请输入分钟："))
    seconds = convert_to_seconds(minutes)
    print(f"秒数为{seconds}")

if __name__ == "__main__":
    main()