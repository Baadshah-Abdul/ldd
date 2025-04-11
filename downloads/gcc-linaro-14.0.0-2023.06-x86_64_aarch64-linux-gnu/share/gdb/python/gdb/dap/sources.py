# Copyright 2023 Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

import gdb

from .server import request, capability
from .startup import send_gdb_with_response, in_gdb_thread


@in_gdb_thread
def _sources():
    result = []
    for elt in gdb.execute_mi("-file-list-exec-source-files")["files"]:
        result.append(
            {
                "name": elt["file"],
                "path": elt["fullname"],
            }
        )
    return {
        "sources": result,
    }


@request("loadedSources")
@capability("supportsLoadedSourcesRequest")
def sources(**extra):
    return send_gdb_with_response(_sources)
