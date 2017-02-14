#!/usr/bin/env python

import sys
import toml
import json
from tabulate import tabulate

field_names = ['pos', 'size', 'name', 'value', 'desc']
field_title = ['Position', 'Size', 'Name', 'Value', 'Description']

common_fields = [
    {'name': 'CRC', 'size': 2, 'desc': 'Cyclic redundancy check'},
    {'name': 'Command number'},
    {'name': 'Packet size', 'desc': 'Number of bytes, excluding the header'},
]


def title(text, char='-'):
    return '\n%s\n%s\n' % (text, char*len(text))


def fields_table(fields, number):
    """Build a table from a list of fields."""
    pos = 0
    fields = common_fields + fields

    for field in fields:
        field['pos'] = pos
        field['size'] = field.get('size', 1)
        pos += field['size']

    fields[1]['value'] = number     # fill command number
    fields[2]['value'] = pos - 4    # fill packet size

    table = [[t.get(f) for f in field_names] for t in fields]
    return tabulate(table, field_title, tablefmt='rst')


def print_fields(fields, title, number):
    print "\n**%s:**\n" % title
    if type(fields) in (str, unicode):
        print fields
    else:
        print fields_table(fields, number)

def print_command(cmd, name):
    print title(name)
    print cmd['desc']
    number = cmd['number']

    if cmd.get('rw'):
        cmd_rd = cmd['command'][:]
        cmd_rd.pop()
        print_fields(cmd_rd, "Command (read)", number)
        print_fields(cmd['command'], "Command (write)", number)
        print_fields(cmd['command'], "Response", number)
    else:
        if cmd.has_key('command'):
            print_fields(cmd['command'], "Command", number)
        if cmd.has_key('response'):
            print_fields(cmd['response'], "Response", number)


def command_list(commands):
    table = [[k+'_', commands[k]['number'], commands[k]['desc']]
             for k in sorted(commands)]
    return tabulate(table, ['Name', 'Number', 'Description'], tablefmt='rst')


if __name__ == '__main__':
    filename = sys.argv[1]
    commands = toml.load(open(filename))

    print ".. _`Serial commands`:\n"
    print title("Serial commands", '=')

    print title("List of commands")
    print command_list(commands)

    for name in sorted(commands):
        cmd = commands[name]
        print_command(cmd, name)
