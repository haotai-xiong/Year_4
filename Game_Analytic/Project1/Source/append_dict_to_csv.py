import csv
# Function to append data to a CSV file
def append_dict_to_csv(file_path, dict_data):
   # Check if the file exists
   try:
       with open(file_path, 'x', newline='') as csvfile:
           writer = csv.DictWriter(csvfile, fieldnames=dict_data.keys())
           writer.writeheader()
           writer.writerow(dict_data)
   except FileExistsError:
       # File exists, append the data
       with open(file_path, 'a', newline='') as csvfile:
           writer = csv.DictWriter(csvfile, fieldnames=dict_data.keys())
           writer.writerow(dict_data)