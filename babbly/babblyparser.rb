# Copyright (C) 2006 Nicolas Dufour
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

require 'optparse'
require 'optparse/time'
require 'ostruct'

class BabblyParser

	CODES = %w[iso-2022-jp shift_jis euc-jp utf8 binary]
	CODE_ALIASES = { "jis" => "iso-2022-jp", "sjis" => "shift_jis" }

	#
	# Return a structure describing the options.
	#
	def self.parse(args)
		# The options specified on the command line will be collected in *options*.
		# We set default values here.
		options = OpenStruct.new
		options.length = 6
		options.nbwords = 10
		options.topics = []

		opts = OptionParser.new do |opts|
			opts.banner = "Usage: babbly.rb [options]"

			opts.separator ""
			opts.separator "Specific options:"

			# Mandatory argument.
			opts.on("-n", "--nbwords #",
		"Specify the number of generated words") do |nb|
				options.nbwords = nb.to_i
		end

			opts.on("-l", "--length #",
		"Specify the minimum length") do |length|
				options.length = length.to_i
		end

			# List of arguments.
			opts.on("-t","--topic weigth,filename", Array, "add a topic with its weight") do |list|
				options.topics << list
			end

			opts.separator ""
			opts.separator "Common options:"

			# No argument, shows at tail.  This will print an options summary.
			# Try it and see!
			opts.on_tail("-h", "--help", "Show this message") do
				puts opts
				exit
			end

			# Another typical switch to print the version.
			opts.on_tail("-v","--version", "Show version") do
				puts OptionParser::Version.join('.')
				exit
			end
		end

		opts.parse!(args)
		options
	end  # parse()

end  # class OptparseExample
