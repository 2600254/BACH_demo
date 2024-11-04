import random

def format_numbers(numbers):
    return [f"{float(num):.2f}" for num in numbers]
    
if __name__ == '__main__':
    numbers = [str(random.uniform(0, 10)) for _ in range(16000)]
    print(','.join(format_numbers(numbers)))