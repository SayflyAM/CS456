rules = {
          "hungry":"You should eat something.",
          "thirsty":"You should drink water.",
          "tired":"You should rest or sleep"


        
        }

def common_sesne_response(text):
    text = text.lower()

    for keyword, response in rules.items():
        if keyword in text:
            return response
    return "I am not sure, but think about the safest and smartest action."

print("Common Sense Assistant")
print("Type exit to stop.\n")


while True:
    user_input = input("You: ")


    if user_input.lower() == "exit":
        print("Assistant: Goodbye")
        break
    print("Assistant:",common_sesne_response(user_input))

