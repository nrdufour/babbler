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

class Scenario

	def initialize
		@topics = Array.new
		@distribution = nil
		@total_weight = 0.0
	end

	def add_topic(weight, filename)
		current_topic = Topic.new(filename, weight)
		current_topic.read
		@topics << current_topic
		@total_weight = @total_weight + weight
	end

	def create_distribution
		distribution_size = @total_weight * 10
		@distribution = Array.new(distribution_size).fill(nil)

		@topics.sort {|t1,t2| t1.weight <=> t2.weight }

		counter = 0
		@topics.each do |topic|
			period = @total_weight / topic.weight

			index = 0.0
			while index <= (distribution_size - 1)
				if (@distribution[index] != nil) and (counter > 0) then
					index = index + 1
					next
				end
				@distribution[index] = topic
				index = index + (period*10)
			end
			counter = counter + 1
		end

		@distribution = @distribution.compact    
	end

	def pick_topic
		create_distribution if @distribution == nil
		choice = rand * @total_weight
		@distribution[choice]
	end

end
