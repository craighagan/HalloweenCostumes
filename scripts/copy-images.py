from __future__ import print_function
from glob import glob
import exifread
import argparse
import re
import datetime
import os
import shutil


BASEDIR = '/Volumes/Photos/pictures'


def get_newest_file(basedir=BASEDIR):
    latest_year_folder = sorted(glob(os.path.join(basedir, '2???')))[-1]
    latest_month_folder = sorted(glob(os.path.join(latest_year_folder, '????_??_??')))[-1]
    latest_glob = os.path.join(latest_month_folder, '*JPG')
    #print("latest", latest_glob)
    latest_file = sorted(glob(latest_glob))[-1]
    tags = exifread.process_file(open(latest_file))
    datestring = tags['Image DateTime'].values
    return datetime.datetime.strptime(datestring, "%Y:%m:%d %H:%M:%S")


class JPGTransformer(object):
    def __init__(self, filename, basedir=BASEDIR, dry_run=True):
        self.original_filename = filename
        self.basedir = basedir
        self.latest_copied_file = get_newest_file()
        self.dry_run = dry_run

    @property
    def tags(self):
        if hasattr(self, '_tags'):
            return self._tags
        self._tags = exifread.process_file(open(self.original_filename))
        return self._tags

    @property
    def create_date(self):
        if hasattr(self, '_create_date'):
            return self._create_date
        datestring = self.tags['Image DateTime'].values
        create_date = datetime.datetime.strptime(datestring, "%Y:%m:%d %H:%M:%S")
        self._create_date = create_date
        return self._create_date

    @property
    def should_copy(self):
        retval = (self.create_date > self.latest_copied_file) and (not os.path.exists(self.get_new_filepath()))
        return retval

    def get_new_filepath(self):
        return os.path.join(self.get_new_filedir(), self.get_new_filename())

    def get_new_filedir(self):
        filedir = os.path.join(self.basedir,
                                self.create_date.strftime("%Y"),
                                self.create_date.strftime("%Y_%m_%d")
                                )
        return filedir

    def get_new_filename(self):
        camera_model = self.tags['Image Model'].values
        new_filename = os.path.basename(self.original_filename)[0:3] + \
            camera_model.replace('Canon ', '') + \
            os.path.basename(self.original_filename)[4:]
        return new_filename

    def match_extension(self, src_file, dst_file):
        return dst_file.replace(dst_file[-4:], src_file[-4:])

    def get_file_pattern(self):
        return self.original_filename[0:-3] + "*"

    def copy_file(self):
        if self.should_copy:
            new_file_path = self.get_new_filedir()
            if not os.path.exists(new_file_path):
                print("would make directory %s" % new_file_path)
                if not self.dry_run:
                    os.makedirs(new_file_path)


            original_file_pattern = self.get_file_pattern()

            for file_to_copy in glob(original_file_pattern):
                new_filename = os.path.join(new_file_path,
                                            self.match_extension(file_to_copy,
                                            self.get_new_filename())) #fix for cr2

                print("would copy %s to %s" % (file_to_copy, new_filename))
                if not self.dry_run:
                    shutil.copyfile(file_to_copy, new_filename)


if __name__ == "__main__":
    dir = '/Volumes/EOS_DIGITAL/DCIM/101EOS5D'
    dir = '/Volumes/Untitled/DCIM/100EOS5D'
    for filename in glob(os.path.join(dir, '*JPG')):
#    for filename in glob(os.path.join(dir, 'J52A43*JPG')):
        print("checking file %s" % filename)
        t = JPGTransformer(filename, dry_run=False)
        t.copy_file()
