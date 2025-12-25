#!/usr/bin/env python3
"""
Create a Google Sheets-friendly version of the final evolutions data.
Creates both CSV and TSV (tab-separated) versions for easy import.
"""

import csv

CSV_INPUT = "final_evolutions_data_changes.csv"
TSV_OUTPUT = "final_evolutions_data_changes.tsv"

# Read CSV and create TSV version
with open(CSV_INPUT, 'r', encoding='utf-8') as csvfile:
    reader = csv.reader(csvfile)
    rows = list(reader)

# Write TSV version (tab-separated, better for copy-paste)
with open(TSV_OUTPUT, 'w', encoding='utf-8', newline='') as tsvfile:
    writer = csv.writer(tsvfile, delimiter='\t')
    writer.writerows(rows)

print(f"✓ Created {TSV_OUTPUT} (tab-separated version)")
print(f"✓ Original CSV: {CSV_INPUT}")
print(f"\nBoth files are ready for Google Sheets!")
print(f"\nFor copy-paste: Use the TSV file (.tsv)")
print(f"For file import: Use either CSV or TSV file")


