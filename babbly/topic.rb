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

class Topic

	attr_reader :filename, :weight

	def initialize(filename, weight)
		@filename = filename
		@weight   = weight
		@words    = Array.new
	end

	def to_s
    "[Topic #{@filename} #{@weight}]"
	end

	def read
		@words.clear

		topicFile = File.open(@filename, "r")

		topicFile.each_line("\n") do |line|
			word = line.strip
			@words << word
		end

		@words = @words.sort
	end

	def pick_char(index, previous)
		# selection des mots
		selection = Array.new
		previous_index = index - 1
		@words.each do |word|
			if previous_index < 0 then
				selection << word
			else
				if word.length >= index+1 then
					if word[previous_index].chr == previous then
						selection << word
					end
				end
			end
		end

		# choix au hasard du mot
		choice = nil
		if selection.size > 0 then
			choice = selection[rand * selection.size]
		end

		# extraction de la lettre
		return nil if choice == nil
		return choice[index].chr
	end

end
