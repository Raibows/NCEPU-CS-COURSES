<template>
  <div>
    <el-row style="margin-top: 20px;">
      <el-col :span="12" :offset="6">
        <el-input placeholder="请输入图书名称（支持模糊搜索）" v-model="keyword" class="input-with-select"
                  @keyup.enter.native="search">
          <el-button slot="append" icon="el-icon-search" @click="search"></el-button>
        </el-input>
      </el-col>
    </el-row>
    <el-row>
      <el-col :span="18" :offset="3" style="margin-top: 20px;">
        <el-table
          :data="tableData"
          border
          style="width: 100%"
          v-loading="loading">
          <el-table-column
            fixed
            prop="isbn"
            label="ISBN"
            width="150">
          </el-table-column>
          <el-table-column
            prop="bookName"
            label="书名"
            min-width="150">
          </el-table-column>
          <el-table-column
            prop="publisher"
            label="出版社">
          </el-table-column>
          <el-table-column
            prop="type"
            label="类型"
            width="80">
            <template slot-scope="scope">
              <el-tag
                :type="getTypeColor(scope.row.type)"
                disable-transitions>{{ getType(scope.row.type) }}
              </el-tag>
            </template>
          </el-table-column>
          <el-table-column
            prop="author"
            label="作者"
            width="150">
          </el-table-column>
          <el-table-column
            prop="publishDate"
            label="出版日期">
          </el-table-column>
          <el-table-column
            fixed="right"
            label="操作"
            width="90">
            <template slot-scope="scope">
              <el-button @click="open_book_form(scope.row)" type="primary" size="small">编辑</el-button>
            </template>
          </el-table-column>
        </el-table>
      </el-col>
    </el-row>
    <el-row style="margin-top: 20px; margin-bottom: 20px ">
      <el-col :span="6" :offset="8">
        <el-pagination
          @size-change="handleSizeChange"
          @current-change="handleCurrentChange"
          :current-page="currentPage"
          :page-sizes="[5, 10, 30, 50]"
          :page-size="pageSize"
          layout="total, sizes, prev, pager, next, jumper"
          :total="total">
        </el-pagination>
      </el-col>
    </el-row>
    <book ref="book_form"/>
  </div>
</template>

<script>

import Book from "@/views/maintain/maintain/components/Book";
import {queryBook} from "@/api/book";

export default {
  name: 'Maintain-Maintain',
  components: {Book},
  data() {
    return {
      loading: true,
      keyword: '',
      total: 0,
      pageSize: 10,
      currentPage: 1,
      tableData: []
    }
  },
  created() {
    this.search()
  },
  computed: {},
  methods: {
    search() {
      this.loading = true
      queryBook({name: this.keyword, page: this.currentPage - 1, size: this.pageSize}).then(response => {
        this.tableData = response.data.content
        this.pageSize = response.data.pageable.pageSize
        this.currentPage = response.data.pageable.pageNumber + 1
        this.total = response.data.totalElements
        this.loading = false
      })
    },
    handleSizeChange(val) {
      this.pageSize = val
      this.search()
    },
    handleCurrentChange(val) {
      this.currentPage = val
      this.search()
    },
    open_book_form(row) {
      this.$refs['book_form'].visible = true
      this.$refs['book_form'].book = row
    },
    getType(type) {
      switch (type) {
        case 1:
          return '编程'
        case 2:
          return '青春'
        case 3:
          return '历史'
      }
    },
    getTypeColor(type) {
      switch (type) {
        case 1:
          return 'primary'
        case 2:
          return 'success'
        case 3:
          return 'info'
      }
    }
  }
}
</script>

<style lang="scss" scoped>

</style>
