<template>
  <div>
    <el-row>
      <el-col :span="12" :offset="6" style="margin-top: 60px">
        <el-row>
          <el-col :span="4">
            <el-select v-model="type" placeholder="请选择">
              <el-option label="全部" :value="1"></el-option>
              <el-option label="图书名" :value="2"></el-option>
              <el-option label="作者名" :value="3"></el-option>
            </el-select>
          </el-col>
          <el-col :span="20">
            <el-input placeholder="请输入内容" v-model="keyword" class="input-with-select" @keyup.enter.native="search">
              <el-button slot="append" icon="el-icon-search" @click="search"></el-button>
            </el-input>
          </el-col>
        </el-row>
      </el-col>
    </el-row>
    <el-row>
      <el-col :span="18" :offset="3" style="margin-top: 20px">
        <el-table
          :data="bookList"
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
            width="180">
            <template slot-scope="scope">
              <el-button @click="borrow(scope.row)" plain="true" type="primary" size="small">借书</el-button>
            </template>
          </el-table-column>
        </el-table>
      </el-col>
    </el-row>
    <el-row>
      <el-col :span="6" :offset="6" style="margin-top: 20px ">
        <el-pagination
          @size-change="handleSizeChange"
          @current-change="handleCurrentChange"
          :current-page="currentPage"
          :page-size="pageSize"
          :page-sizes="[5, 10, 30, 50]"
          layout="total, sizes, prev, pager, next, jumper"
          :total="total">
        </el-pagination>
      </el-col>
    </el-row>

  </div>

</template>

<script>
import {queryAllBook} from "../../../api/search";
import {onlyBorrow} from "../../../api/borrow";

  export default {
    name: 'Circulation-Borrow',
    data() {
      return {
        currentPage: 1,
        total: 0,
        pageSize: 10,
        loading: true,
        keyword: '',
        type: 1,
        bookList: []
      }
    },
    created() {
      this.search()
    },
    methods: {
      search() {
        switch (this.type) {
          case 1:
            this.searchByAll()
            return;
          case 2:
            this.searchByBookName()
            return;
          case 3:
            this.searchByAuthor()
            return;
        }
      },
      searchByAll() {
        queryAllBook({
          all: this.keyword,
          page: this.currentPage - 1,
          size: this.pageSize
        }).then(response => {
          if (response.data==null){
            this.$message({type:"warning",message:"暂无此书!"})
          }else {
            this.bookList = response.data.content
            this.pageSize = response.data.pageable.pageSize
            this.currentPage = response.data.pageable.pageNumber + 1
            this.total = response.data.totalElements
            this.loading = false
          }
        })
      },
      searchByAuthor() {
        queryAllBook({
          author: this.keyword,
          page: this.currentPage - 1,
          size: this.pageSize
        }).then(response => {
          if (response.data==null){
            this.$message({type:"warning",message:"暂无此书!"})
          }else {
            this.bookList = response.data.content
            this.pageSize = response.data.pageable.pageSize
            this.currentPage = response.data.pageable.pageNumber + 1
            this.total = response.data.totalElements
            this.loading = false
          }
        })
      },
      searchByBookName() {
        queryAllBook({
          name: this.keyword,
          page: this.currentPage - 1,
          size: this.pageSize
        }).then(response => {
          if (response.data==null){
            this.$message({type:"warning",message:"暂无此书!"})
          }else {
            this.bookList = response.data.content
            this.pageSize = response.data.pageable.pageSize
            this.currentPage = response.data.pageable.pageNumber + 1
            this.total = response.data.totalElements
            this.loading = false
          }
        })
      },
      borrow(row){
        onlyBorrow({stuid:this.$store.getters.userId,isbn:row.isbn}).then(response=>{
          this.$message({
            message: response.msg,
            type: 'success'
          });
        })
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
      },
      handleSizeChange(val) {
        this.pageSize = val
        this.search()
      },
      handleCurrentChange(val) {
        this.currentPage = val
        this.search()
      },
    }
  }
</script>

<style scoped>
  .el-select .el-input {
    width: 130px;
  }

  .input-with-select .el-input-group__prepend {
    background-color: #fff;
  }
</style>
