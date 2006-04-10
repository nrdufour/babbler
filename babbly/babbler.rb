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

class Babbler

	def initialize(scenario, nbwords, length)
		@scenario = scenario
		@nbwords = nbwords
		@length = length
	end

	def run
		@nbwords.times do
			word = ""
			word_counter = 0
			while word.length < @length do
				word = babble
				word_counter = word_counter.next
				if word_counter > 100 then
					word = nil
					break
				end
			end
			puts "#{word} (#{word_counter} attemps)" if word != nil
		end
	end

	def babble
		index = 0
		previous = nil

		new_word = ''
		loop {
			topic = @scenario.pick_topic
			if topic == nil then
				puts "You havent given any topic to work with !!"
				exit
			end
			current_char = @scenario.pick_topic.pick_char(index,previous)
			if (current_char == nil) then break end
			new_word = new_word + current_char

			previous = current_char
			index = index + 1
		}

		return new_word
	end

end
