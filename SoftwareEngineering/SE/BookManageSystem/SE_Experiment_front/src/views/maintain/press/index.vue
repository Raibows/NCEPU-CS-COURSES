<template>
  <div>
    <el-row style="margin-top: 20px;">
      <el-col :span="12" :offset="6">
        <el-input placeholder="请输入出版社名称（支持模糊搜索）" v-model="keyword" @keyup.enter.native="search"
                  class="input-with-select">
          <el-button slot="append" icon="el-icon-search" @click="search"></el-button>
        </el-input>
      </el-col>
      <el-col :span="2" :offset="1">
        <el-button type="primary" round @click="openForm({}, false)">添加出版社</el-button>
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
            prop="id"
            label="序号"
            width="150">
          </el-table-column>
          <el-table-column
            prop="publisherName"
            label="名称"
            width="300">
          </el-table-column>
          <el-table-column
            prop="publisherAddr"
            label="地址"
            width="300">
          </el-table-column>
          <el-table-column
            prop="phoneNumber"
            label="电话号码"
            width="300">
          </el-table-column>
          <el-table-column
            fixed="right"
            label="操作"
            width="200">
            <template slot-scope="scope">
              <el-button @click="openForm(scope.row, true)" type="primary" size="small">编辑</el-button>
              <el-button type="danger" size="small" @click="deletePublisher(scope.row.id)">删除</el-button>
            </template>
          </el-table-column>
        </el-table>
      </el-col>
    </el-row>
    <el-row style="margin-top: 20px;">
      <el-col :span="12" :offset="6">
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
    <press-form ref="pressForm"/>
  </div>
</template>

<script>

import PressForm from "@/views/maintain/press/components/press_form";
import {deletePublisher, queryAllPublisher} from "@/api/publisher";
import {deleteUser} from "@/api/user";

export default {
  name: 'Maintain-Press',
  components: {PressForm},
  data() {
    return {
      loading: true,
      keyword: '',
      total: 0,
      currentPage: 1,
      pageSize: 5,
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
      queryAllPublisher({
        name: this.keyword,
        page: this.currentPage - 1,
        size: this.pageSize
      }).then(response => {
        this.tableData = response.data.content
        this.pageSize = response.data.pageable.pageSize
        this.currentPage = response.data.pageable.pageNumber + 1
        this.total = response.data.totalElements
        this.loading = false
      })
    },
    deletePublisher(id) {
      this.$confirm('此操作将删除该记录且无法撤销, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'error'
      }).then(() => {
        deletePublisher({id: id}).then(response => {
          this.search()
          this.$message({
            type: 'success',
            message: response.msg
          });
        })
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除'
        });
      });
    },
    handleSizeChange(val) {
      this.pageSize = val
      this.search()
    },
    handleCurrentChange(val) {
      this.currentPage = val
      this.search()
    },
    openForm(row, edit) {
      this.$refs['pressForm'].visible = true;
      this.$refs['pressForm'].press = row;
      this.$refs['pressForm'].edit = edit;
    }
  }
}
</script>

<style lang="scss" scoped>

</style>
